/**
 * Copyright (C) 2010 univmercury, univmercury@gmail.com
 * Version 0.0.1
 * 29/07/2009
 * Distributed under the OpenCV Licence (BSD Licence)
 */

/**
 * \file The K-Means algorithm.
 */

#include "stdafx.h"

#include "cv.h"


#include <iostream>


#ifndef float_t
#define float_t float
#endif//float_t

void kmeans(const CvMat* samples, CvTermCriteria termcrit, CvMat* centers, CvMat* labels);
void assign_labels(const CvMat* samples, const CvMat* centers, CvMat* labels);

/**
 * \brief The K-Means algorithm.
 *
 * \param samples The [nxd] matrix, each row is a sample. n samples, d dimension
 * \param termcrit The Terminate Criteria.
 * \param centers The [kxd] matrix, each row is a cluster center, k centers, d dimension
 * \param labels The [nx1] matrix, each row is a label.
 *
 * \note samples must be of CV_32FC1 or CV64FC1, centers must be of CV_64FC1, labels must be of CV_32SC1.
 * 2009.7.29 code complete, haven't tested.
 * ok.
 */
void kmeans(const CvMat* samples, CvTermCriteria termcrit, CvMat* centers, CvMat* labels)
{
    // check the input parameters.
    
    if (CV_MAT_TYPE(samples->type) != CV_32FC1 && CV_MAT_TYPE(samples->type) != CV_64FC1)
    {
        std::cout << "Error: samples must be of type CV_32FC1 or CV_64FC1" << std::endl;
        return;
    }
    if (CV_MAT_TYPE(centers->type) != CV_64FC1)
    {
        std::cout << "Error: centers must be of type CV_64FC1." << std::endl;
        return;
    }
    if (CV_MAT_TYPE(labels->type) != CV_32SC1)
    {
        std::cout << "Error: labels must be of type CV_32SC1." << std::endl;
        return;
    }
    if (samples->rows != labels->rows )
    {
        std::cout << "The rows of samples and labels must be the same, it is the number of samples." << std::endl;
        return;
    }
    if (samples->cols != centers->cols)
    {
        std::cout << "The columns of samples and centers must be the same, it is the dimension of samples." << std::endl;
        return;
    }
    if (centers->rows > samples->rows)
    {
        std::cout << "Error: the number of clusters must be <= the number of samples." << std::endl;
        return;
    }
    if (labels->cols != 1)
    {
        std::cout << "Error: the labels must be of [nx1] matrix." << std::endl;
        return;
    }

    CvMat* ret_centers = centers; // cache the outter memory, so that it can return correctly.
    
    int numof_samples = samples->rows; // number of samples
    int dimof_samples = samples->cols; // dimension of samples
    int numof_clusters = centers->rows; // number of cluters
 
    if (numof_clusters <1)
    {
        std::cout << "error: Number of clusters should be positive" << std::endl;
        return;
    }

    termcrit = cvCheckTermCriteria(termcrit, 1e-6, 100);
    termcrit.epsilon *= termcrit.epsilon; // use square dist, so ...
    std::cout << "MaxIter: " << termcrit.max_iter << ", Eps: " << termcrit.epsilon << std::endl;


    // begin

    CvMat* old_centers = cvCreateMat(numof_clusters, dimof_samples, CV_64FC1);
    CvMat* counters    = cvCreateMat(1, numof_clusters, CV_32SC1);
    CvMat* temp        = 0;

    int ids_delta = labels->step ? labels->step/(int)sizeof(int) : 1;
    CvRNG rng     = CvRNG(-1);

    // init labels: randomly assign each sample to a cluster.
    for (int i=0; i<numof_samples; ++i)
    {
        labels->data.i[i] = cvRandInt(&rng) % numof_clusters;
    }
    counters->cols = numof_clusters;
    double max_dist = termcrit.epsilon * 2;

    for (int iter=0; iter<termcrit.max_iter; ++iter)
    {
        std::cout << "iteration: " << iter << std::endl;
    
        cvZero(centers);
        cvZero(counters);

        // accumulate the centers
        for (int i=0; i<numof_samples; ++i)
        {
            // s: the i-th sample.
            float_t* s = (float_t*)(samples->data.ptr + i * samples->step);
            // k: the label of s.
            int k = labels->data.i[i*ids_delta];
            // c: the k-th cluster, the label of s is c.
            double* c = (double*)(centers->data.ptr + k*centers->step);
        
            // c += s.
            {
                int j = 0;
                for ( ; j<dimof_samples-4; j+=4)
                {
                    double t0 = c[j  ] + s[j  ];
                    double t1 = c[j+1] + s[j+1];
                    c[j  ] = t0;
                    c[j+1] = t1;

                    t0 = c[j+2] + s[j+2];
                    t1 = c[j+3] + s[j+3];
                    c[j+2] = t0;
                    c[j+3] = t1;
                }
                for ( ; j<dimof_samples; ++j)
                {
                    c[j] += s[j];
                }
            }
            // increase the counter.
            counters->data.i[k]++;
        }

        if (iter > 0)
        {
            max_dist = 0;
        }

        for (int k=0; k<numof_clusters; ++k)
        {
            double* c = (double*)(centers->data.ptr + k*centers->step);

            // compute the cluster center: c = c/m, where m is number of samples in the c cluster.
            if (counters->data.i[k] != 0)
            {
                double scale = 1.0 / counters->data.i[k];
                for (int j=0; j<dimof_samples; ++j)
                {
                    c[j] *= scale;
                }
            }
            else
            {
                int i = cvRandInt(&rng) % numof_samples;
                float_t* s = (float_t*)(samples->data.ptr + i*samples->step);
                for (int j=0; j<dimof_samples; ++j)
                {
                    c[j] = s[j];
                }
            }

            // compare distance between centers and old centers.
            if (iter > 0)
            {
                double dist = 0;
                double* c_o = (double*)(old_centers->data.ptr + k*old_centers->step);

                for (int j=0 ; j<dimof_samples; ++j)
                {
                    double t = c[j] - c_o[j];
                    dist += t*t;
                }

                if (max_dist < dist)
                {
                    max_dist = dist;
                }
            }
        }
        
        // assign labels
        assign_labels(samples, centers, labels);
        
        // check converge
        std::cout << "max_dist: " << max_dist << std::endl;
        if (max_dist < termcrit.epsilon)
        {
            break;
        }
        
        CV_SWAP(centers, old_centers, temp);
    }

    // compute the number of samples in each cluster.
    cvZero(counters);
    for (int i=0; i<numof_samples; ++i)
    {
        counters->data.i[labels->data.i[i]]++;
    }
    
    // ensure that we do not have empty clusters
    for (int k=0; k<numof_clusters; ++k)
    {
        if (counters->data.i[k] == 0)
        {
            // randomly select a sample, and assign it to the k-th cluster.
            for ( ; ; )
            {
                int i = cvRandInt(&rng) % numof_samples; // the i-th samples;
                int kk = labels->data.i[i];  // the kk-th cluster.
                if (counters->data.i[kk] > 1)
                {
                    labels->data.i[i] = k;  // assign label to k.
                    counters->data.i[kk]--; // decrease the kk-th cluster.
                    counters->data.i[k]++;  // increase the k-th cluster.
                    break;
                }
            }
        }
    }
    
    // check whether the outter memory is correct
    if (centers != ret_centers) 
    {
        // now the pointers are
        // centers --> inner memory, with correct centers.
        // ret_centers --> outter memory, same as old_cetners
        // old_centers --> outter memory, with old centers.
        // we need to copy the inner memory to the outter, so that it can return the correct center.
        cvCopy(centers, ret_centers);
        CV_SWAP(centers, old_centers, temp);
    }

    cvReleaseMat(&old_centers);
    cvReleaseMat(&counters);

    // end
    
    // return centers and labels.
}

/**
 * \brief Assign labels to samples.
 *
 * \param samples the [n*d] matrix of samples, each row is a d dimensional sample.
 * \param centers the [k*d] matrix of cluster centers, each row is a center.
 * \param labels the [n*1] matrix of labels, each row is a label.
 * \note the samples are of CV_32FC1 or CV_64FC1, centers must be of CV_64FC1, labels must be of CV32SC1.
 * 2009.7.29 code complete, haven't tested.
 */
void assign_labels(const CvMat* samples, const CvMat* centers, CvMat* labels)
{
    // check the input parameters.
    
    if (CV_MAT_TYPE(samples->type) != CV_32FC1 && CV_MAT_TYPE(samples->type) != CV_64FC1)
    {
        std::cout << "Error: samples must be of type CV_32FC1 or CV_64FC1" << std::endl;
        return;
    }
    if (CV_MAT_TYPE(centers->type) != CV_64FC1)
    {
        std::cout << "Error: centers must be of type CV_64FC1." << std::endl;
        return;
    }
    if (CV_MAT_TYPE(labels->type) != CV_32SC1)
    {
        std::cout << "Error: labels must be of type CV_32SC1." << std::endl;
        return;
    }
    if (samples->rows != labels->rows )
    {
        std::cout << "The rows of samples and labels must be the same, it is the number of samples." << std::endl;
        return;
    }
    if (samples->cols != centers->cols)
    {
        std::cout << "The columns of samples and centers must be the same, it is the dimension of samples." << std::endl;
        return;
    }
    if (centers->rows > samples->rows)
    {
        std::cout << "Error: the number of clusters must be <= the number of samples." << std::endl;
        return;
    }
    if (labels->cols != 1)
    {
        std::cout << "Error: the labels must be of [nx1] matrix." << std::endl;
        return;
    }

    // begin
    
    int numof_samples = samples->rows;
    int dimof_samples = samples->cols*CV_MAT_CN(samples->type);
    int numof_clusters = centers->rows;
    int ids_delta = labels->step ? labels->step/(int)sizeof(int) : 1;

    for (int i=0; i<numof_samples; ++i)
    {
        float_t* s = (float_t*)(samples->data.ptr + i*samples->step);
        int    best_k   = 0;
        double min_dist = DBL_MAX;

        // find the best clusters, the minimal distance between s and c.
        for (int k=0; k<numof_clusters; ++k)
        {
            double* c = (double*)(centers->data.ptr + k*centers->step);
            double dist = 0;

            // compute the Euclidean sqaure distance between s and c.
            {     
                int j = 0;
                for ( ; j<dimof_samples-4; j+=4)
                {
                    double t0 = c[j  ] - s[j  ];
                    double t1 = c[j+1] - s[j+1];
                    dist += t0*t0 + t1*t1;

                    t0 = c[j+2] - s[j+2];
                    t1 = c[j+3] - s[j+3];
                    dist += t0*t0 + t1*t1;
                }
                for ( ; j<dimof_samples; ++j)
                {
                    double t0 = c[j] - s[j];
                    dist += t0*t0;
                }
            }

            // update the best cluster.
            if (min_dist > dist)
            {
                min_dist = dist;
                best_k   = k;
            }
        }

        // assign label to the best k. 
        labels->data.i[i*ids_delta] = best_k;
    }    

    // end
}

