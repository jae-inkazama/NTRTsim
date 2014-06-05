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

#ifndef SRC_CORE_IMPEDANCECONTROL_H_
#define SRC_CORE_IMPEDANCECONTROL_H_

/**
 * @file ImpedanceControl.h
 * @brief Contains the definition of class ImpedanceControl.
 * $Id$
 */

/**
 * \dir core
 * @brief The core simulation and base level models.
 * 
 * The core directory contains all of the necessary components for
 * modeling and simulation. This includes:
 * - the world tgWorld, 
 * - simulation control in tgSimulation,
 * - views of the simulation: tgSimView and tgSimViewGraphics
 * - rendering functions tgBulletRenderer, based on tgModelVisitor
 * - the base class for models tgModel,
 * - components of models such as tgRod and tgLinearString
 * - the ability to tag models and components with tgTags and tgTaggable
 * - basic components of controllers tgSubject and tgObserver
 */
// Forward references
class tgBaseString;
/**
 * Influences the Muscle tension using length and velocity.
 */
class ImpedanceControl
{
 public:
     
     ///Constructors
     /**
     * The null constructor sets defaults values for the
     * member variables.
     */
        ImpedanceControl();

    /**
     * This constructor supplies initial values for all member
     * variables.
     * @param[in] offsetTension the initial value for the offset
     * tension property; must be non-negative
     * @param[in] lengthStiffness the initial value for the length
     * stiffness property; must be non-negative
     * @param[in] velStiffness the initial value for the velocity
     * stiffness property; must be non-negative
     */
    ImpedanceControl(double offsetTension,
             double lengthStiffness,
             double velStiffness);
    
    ///Control Functions

    /**
     * @param[in] Control a tgLinearString given a new offset force and a
     * new offset velocity.
     * @param[in] mString a pointer to a tgLinearString; must not be NULL
     * @param[in] deltaTimeSeconds the number of seconds since the
     * last call
     * @param[in] newPosition the current position of the Muscle
     * @todo Make mMuscle a reference.
     * @todo should we add an offset position so it can just control??
     */
    double control(tgBaseString* const mString,
                    double deltaTimeSeconds,
                    double newPosition,
                    double offsetVel = 0);
    
                    
    double controlTension(tgBaseString* const mString,
                    double deltaTimeSeconds,
                    double newPosition,
                    double offsetTension,
                    double offsetVel = 0);

    /**
     * Set the value of the offset tension property.
     * @param[in] the new value for the offset tension property
     * must be non-negative
     */
    void setOffsetTension(double offsetTension);

    /**
     * Set the value of the length stiffness property.
     * @param[in] the new value for the length stiffness property
     * must be non-negative
     */
    void setLengthStiffness(double lengthStiffness);

    /**
     * Set the value of the velocity stiffness property.
     * @param[in] the new value for the velocity stiffness property
     * must be non-negative
     */
    void setVelStiffness(double velStiffness);

    /**
     * Return the value of the offset tension property.
     * @return the value of the offset tension property
     */
    double getOffsetTension() const
    {
            return _offsetTension;
    }

    /**
     * Return the value of the length stiffness property.
     * @return the value of the length stiffness property
     */
    double getLengthStiffness() const
    {
            return _lengthStiffness;
    }

    /**
     * Return the value of the velocity stiffness property.
     * @return the value of the velocity stiffness property
     */
    double getVelStiffness() const
    {
            return _velStiffness;
    }
        
 protected:

    /**
     * A force component.
     * Must be non-negative to ensure stability.
     * The units are application-dependent, e.g., Newtons or
     * centinewtons.
     * @todo rename m_offsetTension.
     */
    double _offsetTension;

    /**
     * Used to determine the force component attributable to a
     * Muscle's length.
     * Must be non-negative to ensure stability.
     * The units are kg/sec^2. When multiplied by the Muscle length
     * it gives a force component.
     * @todo Rename m_lengthStiffness.
     */
    double _lengthStiffness;

    /**
     * Used to determine the force component attributable to a
     * Muscle's velocity.
     * The units are kg/sec. When multiplied by the Muscle velocity
     * it gives a force component.
     * Must be non-negative to ensure stability
     * @todo Rename m_velocityStiffness.
     */
    double _velStiffness;

 private:
        
    /** Integrity predicate. */
    bool invariant() const;
};

#endif  // SRC_CORE_IMPEDANCECONTROL_H_
