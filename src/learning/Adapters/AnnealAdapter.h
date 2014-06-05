/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

#ifndef ANNEALADAPTER_H_
#define ANNEALADAPTER_H_

/**
 * @file AnnealAdapter.h
 * @brief Defines a class AnnealAdapter to pass parameters from AnnealEvolution to a controller.
 * Adapting NeuroEvolution to do Simulated Annealing
 * @date April 2014
 * @author Brian Tietz and Atil Iscen
 * $Id$
 */

/**
 * \dir learning
 * @brief Tools for machine learning on tensegrity structures.
 * 
 * Contains an evolution scheme that can be configured for MonteCarlo,
 * gaussian sampling or simulated annealing. Also contains adapters to
 * read parameters in and out of evolution objects, and a class to
 * read a simulation configuration from a .ini text file
 */
 
 /**
  * \dir learning/Adapters
  * @brief A class that passes parameters between AnnealEvolution and a controller
  * 
  * Depends upon both AnnealEvolution and Configuration
  */

#include <vector>
#include "learning/AnnealEvolution/AnnealEvolution.h"
#include "learning/AnnealEvolution/AnnealEvoMember.h"

class AnnealAdapter
{
public:
    AnnealAdapter();
    ~AnnealAdapter();
    /**
     * Initialize needs to be called at the beginning of each trial
     * For NTRT this means main or simulator needs to own the pointer to
     * AnnealEvolution, we can't create it here
     */
    void initialize(AnnealEvolution *evo,bool isLearning,configuration config);
    std::vector<std::vector<double> > step(double deltaTimeSeconds, std::vector<double> state);
    void endEpisode(std::vector<double> state);

private:
    int numberOfActions;
    int numberOfStates;
    int numberOfControllers;
    AnnealEvolution *annealEvo;
    std::vector< AnnealEvoMember *>currentControllers;
    std::vector<double> initialPosition;
    double errorOfFirstController;
    double totalTime;
};

#endif /* ANNEALADAPTER_H_ */
