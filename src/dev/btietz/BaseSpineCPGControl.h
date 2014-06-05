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

#ifndef BASE_SPINE_CPG_CONTROL_H
#define BASE_SPINE_CPG_CONTROL_H

#include <vector>
#include "boost/multi_array.hpp"

#include "core/tgObserver.h"
#include "sensors/tgDataObserver.h"

#include "learning/Adapters/AnnealAdapter.h"

//This should probably be a forward declaration
#include "BaseSpineModelLearning.h"

// Forward Declarations
class ImpedanceControl;
class AnnealEvolution;
class configuration;
class tgCPGStringControl;
class CPGEquations;

typedef boost::multi_array<double, 2> array_2D;
typedef boost::multi_array<double, 4> array_4D;

class BaseSpineCPGControl : public tgObserver<BaseSpineModelLearning>
{
public:

struct Config
    {
    public:
        /**
         * The only constructor. 
         */
        Config( int ss,
        int tm,
        int om,
        int param,
        int segnum = 6,
        double ct = 0.1,
        double la = 0,
        double ha = 30,
        double lp = -1 * M_PI,
        double hp = M_PI,
        double kt = 0.0,
        double kp = 1000.0,
        double kv = 100.0,
        bool def = true,
        double cl = 10.0);
      
		// Learning Parameters
		const int segmentSpan; // 3 possible muscles touching two rigid bodies
		const int theirMuscles; // 8 muscles in a segment 
		const int ourMuscles; // same as above
		const int params; // Number of parameters per edge
		const int segmentNumber;
        
        // CPG control frequency
        const double controlTime;
        
        // Limit Params
        const double lowAmp;
        const double highAmp;
        const double lowPhase;
        const double highPhase;
        
		// Parameters for Impedance Controllers
		const double tension;
		const double kPosition;
		const double kVelocity;
		const bool useDefault;
        const double controlLength;    
    };

    BaseSpineCPGControl(BaseSpineCPGControl::Config config,	
							std::string args,
                            std::string ec = "edgeConfig.ini",
                            std::string nc = "nodeConfig.ini");
    
    ~BaseSpineCPGControl() {}
    
    virtual void onStep(BaseSpineModelLearning& subject, double dt);
    
    virtual void onSetup(BaseSpineModelLearning& subject);
    
    virtual void onTeardown(BaseSpineModelLearning& subject);

protected:
    /**
     * Takes a vector of parameters reported by learning, and then 
     * converts it into a format used to assign to the CPGEdges
     * Note that if the CPG edges change, this will need to change
     */
    virtual array_4D scaleEdgeActions (std::vector< std::vector <double> > actions);
    virtual array_2D scaleNodeActions (std::vector< std::vector <double> > actions);
    
    virtual void setupCPGs(BaseSpineModelLearning& subject, array_2D nodeActions, array_4D edgeActions);

    CPGEquations* m_pCPGSys;
    
    std::vector<tgCPGStringControl*> m_allControllers;
    
private:  
	BaseSpineCPGControl::Config m_config;

    std::string edgeConfigFilename;
    std::string nodeConfigFilename;
    
    configuration nodeConfigData;
    configuration edgeConfigData;
    
    AnnealEvolution edgeEvolution;
    AnnealEvolution nodeEvolution;
    
    AnnealAdapter edgeAdapter;
    AnnealAdapter nodeAdapter;
    
    bool nodeLearning;
    bool edgeLearning;
    
    std::vector<double> initConditions;
    
    std::size_t segments;
    
    tgDataObserver m_dataObserver;
    
    double m_updateTime;
    
};

#endif // BASE_SPINE_CPG_CONTROL_H
