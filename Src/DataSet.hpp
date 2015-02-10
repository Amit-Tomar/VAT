#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include <cmath>
#include "DataPoint.hpp"
#include "Statistics.h"
#include "GlobalSettingsData.h"

template< typename dataPointFeatureType, typename dataPointDistanceType>

class DataSet
{
public:
    DataSet(){}
    virtual ~ DataSet() {}    

    virtual dataPointDistanceType getDistanceBetweenPoints(DataPoint <dataPointFeatureType> point1,DataPoint <dataPointFeatureType> point2, dissimilarityFunction functionType )
    {
        dataPointDistanceType distance = 0 ;

        if( e_euclidean == functionType )
        {
            for( int i = 0 ; i < point1.getFeatureVector().size() ; ++i )
            {
                distance += pow ( (dataPointFeatureType)point1.getFeatureI(i)-point2.getFeatureI(i), 2 );
            }
            return (dataPointDistanceType) sqrt(distance);
        }

        else if( e_cosine == functionType )
        {
            // Cos Theta = A.B / |A| |B|

              dataPointDistanceType dotProduct    = 0.0;
              dataPointDistanceType vec1Magnitude = 0.0;
              dataPointDistanceType vec2Magnitude = 0.0;

              for (int i = 0; i < point1.getFeatureVector().size(); i++)
              {
                  dotProduct    += (point1.getFeatureI(i) * point2.getFeatureI(i)) ;
                  vec1Magnitude += (point1.getFeatureI(i) * point1.getFeatureI(i));
                  vec2Magnitude += (point2.getFeatureI(i) * point2.getFeatureI(i));
              }

              dataPointDistanceType cosineDistance =  (dotProduct / (sqrt(vec1Magnitude) * sqrt(vec2Magnitude)));
              cosineDistance = acos(cosineDistance) * 180.0 / 3.14159265 ;
              return cosineDistance;
        }

        else if( e_jaccard == functionType )
        {
            // Jacc coeff. = A.B / (|A|^2 |B|^2 - A.B)

              dataPointDistanceType dotProduct    = 0.0;
              dataPointDistanceType vec1MagnitudeSquare = 0.0;
              dataPointDistanceType vec2MagnitudeSquare = 0.0;

              for (int i = 0; i < point1.getFeatureVector().size(); i++)
              {
                  dotProduct    += (point1.getFeatureI(i) * point2.getFeatureI(i)) ;
                  vec1MagnitudeSquare += (point1.getFeatureI(i) * point1.getFeatureI(i) );
                  vec2MagnitudeSquare += (point2.getFeatureI(i) * point2.getFeatureI(i) );
              }

              return (dotProduct / ( vec1MagnitudeSquare + vec2MagnitudeSquare - dotProduct ));;
        }

        else if( e_manhattan == functionType )
        {
              dataPointDistanceType manhattanDistance = 0.0;

              for (int i = 0; i < point1.getFeatureVector().size(); i++)
              {
                  manhattanDistance += abs(point1.getFeatureI(i) - point2.getFeatureI(i)) ;
              }

              return manhattanDistance;
        }

        else if( e_canberra == functionType )
        {
              dataPointDistanceType canberraDistance = 0.0;

              for (int i = 0; i < point1.getFeatureVector().size(); i++)
              {
                  if( 0 == ( abs(point1.getFeatureI(i)) + abs(point2.getFeatureI(i)) ) )
                      canberraDistance += 0;
                  else
                      canberraDistance += (abs(point1.getFeatureI(i) - point2.getFeatureI(i)) / ( abs(point1.getFeatureI(i)) + abs(point2.getFeatureI(i)) )) ;
              }

              return canberraDistance;
        }

        else if( e_mahalanobis == functionType )
        {
            std::cerr << "To be done" << std::endl ;
        }

        // http://en.wikipedia.org/wiki/Pearson_product-moment_correlation_coefficient#Pearson.E2.80.99s_distance
        else if( e_pearson == functionType )
        {
            dataPointDistanceType pearsonCoefficient = 0.0;
            dataPointDistanceType numerator = 0.0, denominator1 = 0.0, denominator2 = 0.0;

            for (int i = 0; i < point1.getFeatureVector().size(); i++)
            {
                numerator += (point1.getFeatureVector()[i] - dataStatisticList[i].mean)*( point2.getFeatureVector()[i] - dataStatisticList[i].mean );
            }

            for (int i = 0; i < point1.getFeatureVector().size(); i++)
            {
                denominator1  += (point1.getFeatureVector()[i] - dataStatisticList[i].mean)*( point1.getFeatureVector()[i] - dataStatisticList[i].mean );
            }

            denominator1 = sqrt(denominator1);

            for (int i = 0; i < point1.getFeatureVector().size(); i++)
            {
                denominator2  += (point2.getFeatureVector()[i] - dataStatisticList[i].mean)*( point2.getFeatureVector()[i] - dataStatisticList[i].mean );
            }

            denominator2 = sqrt(denominator2);

            pearsonCoefficient = numerator / (denominator1 * denominator2);

            return 1-pearsonCoefficient ;
        }

        else
        {
            std::cerr << "Invalid dissimilarity function type" << std::endl ;
        }
    }

    std::vector <DataPoint<dataPointFeatureType> > & getDataPointsList()
    {
        return dataPointsList;
    }

    void pushDataPoint(DataPoint<dataPointFeatureType> data)
    {
        dataPointsList.push_back(data);
        dataPointOrderList.push_back(dataPointOrderList.size());
    }

    void randomRearrangeDataset()
    {
            for( unsigned int i = 0 ; i < dataPointsList.size() ; ++i)
            {
                int randomDatavaluePosition = rand() % dataPointsList.size();

                DataPoint<dataPointFeatureType> temp = dataPointsList[randomDatavaluePosition];
                dataPointsList[randomDatavaluePosition] = dataPointsList[i];
                dataPointsList[i] = temp;

                unsigned int tempdataOrderPosn = dataPointOrderList[randomDatavaluePosition];
                dataPointOrderList[randomDatavaluePosition] = dataPointOrderList[i];
                dataPointOrderList[i] = tempdataOrderPosn;
            }
    }

    void normalizeDataset()
    {        
        std::cout << "Stats calculated" << std::endl ;
        evaluateStats();

        for( int i = 0 ; i < dataPointsList.size() ; ++i )
        {
            for( int j = 0 ; j < dataPointsList[i].totalFeatures() ; ++j )
                dataPointsList[i].setFeatureI(j , (dataPointsList[i].getFeatureI(j) - dataStatisticList[j].mean) / dataStatisticList[j].stdDeviation );
        }
    }

    void evaluateStats()
    {
        dataStatisticList.resize(dataPointsList[0].totalFeatures());

        std::cout << dataPointsList[0].totalFeatures() << std::endl ;

        // Calculate Mean
        for( int i = 0 ; i < dataPointsList.size() ; ++i )
        {
            for( int j = 0 ; j < dataPointsList[i].totalFeatures() ; ++j )
                dataStatisticList[j].mean += dataPointsList[i].getFeatureI(j);
        }

        for( int i = 0 ; i < dataPointsList[i].totalFeatures() ; ++i )
            dataStatisticList[i].mean /= dataPointsList.size();

        // Calculate Variance
        for( int i = 0 ; i < dataPointsList.size() ; ++i )
        {
            for( int j = 0 ; j < dataPointsList[i].totalFeatures() ; ++j )
                dataStatisticList[j].variance += pow(dataPointsList[i].getFeatureI(j) - dataStatisticList[j].mean,2) ;
        }

        for( int i = 0 ; i < dataPointsList[i].totalFeatures() ; ++i )
        {
            dataStatisticList[i].variance /= dataPointsList.size();
            dataStatisticList[i].stdDeviation = sqrt(dataStatisticList[i].variance);
        }

        for( int j = 0 ; j < dataPointsList[j].totalFeatures() ; ++j )
            std::cout << "Feature " << j << " Mean: " << dataStatisticList[j].mean << " Variance: " << dataStatisticList[j].variance << " StdDeviation: " << dataStatisticList[j].stdDeviation << std::endl ;
    }

private:

    std::vector <DataPoint<dataPointFeatureType> > dataPointsList;
    std::vector <Stats> dataStatisticList;
    std::vector <unsigned int> dataPointOrderList;
};

#endif // DATASET_H
