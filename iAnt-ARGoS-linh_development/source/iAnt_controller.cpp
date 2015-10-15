#include "iAnt_controller.h"
#include <stdlib.h>
/*****
 * Initialize most basic variables and objects here. Most of the setup should
 * be done in the Init(...) function instead of here where possible.
 *****/
iAnt_controller::iAnt_controller() :
    compass(NULL),
    motorActuator(NULL),
    proximitySensor(NULL),
    data(NULL),
    RobotForwardSpeed(0.0),
    RobotTurningSpeed(0.0)
{}

/*****
 * Initialize the controller via the XML configuration file. ARGoS typically
 * wants objects & variables initialized here instead of in the constructor(s).
 *****/
void iAnt_controller::Init(TConfigurationNode& node) {
    /* Shorter names, please. #This_Is_Not_Java */
    typedef CCI_PositioningSensor            CCI_PS;
    typedef CCI_DifferentialSteeringActuator CCI_DSA;
    typedef CCI_FootBotProximitySensor       CCI_FBPS;

    /* Initialize the robot's actuator and sensor objects. */
    motorActuator   = GetActuator<CCI_DSA>("differential_steering");
    compass         = GetSensor<CCI_PS>   ("positioning");
    proximitySensor = GetSensor<CCI_FBPS> ("footbot_proximity");

    TConfigurationNode iAnt_params = GetNode(node, "iAnt_params");
    GetNodeAttribute(iAnt_params, "RobotForwardSpeed", RobotForwardSpeed);
    GetNodeAttribute(iAnt_params, "RobotTurningSpeed", RobotTurningSpeed);
    GetNodeAttribute(iAnt_params, "AngleToleranceInDegrees", angleInDegrees);

    AngleToleranceInRadians.Set(-ToRadians(angleInDegrees),ToRadians(angleInDegrees));
    
    stepSize = 0.1; /* Assigns the robot's stepSize */
    startPosition = CVector3(0.0, 0.0, 0.0);
}


bool iAnt_controller::Stop ()
{
    bool stop = false;

    if(stopTimeStep > 0)
    {
        stopTimeStep--;
        stop = true;
    }
    return stop;

}

void iAnt_controller::SetStop(size_t stop_time_in_seconds)
{
    stopTimeStep += stop_time_in_seconds* data->TicksPerSecond;

}

void iAnt_controller::GetPattern(string ith_Pattern)
{
    copy(ith_Pattern.begin(),ith_Pattern.end(),back_inserter(tempPattern));
    reverse(tempPattern.begin(), tempPattern.end());
}

// /*****
//  *
//  *****/
void iAnt_controller::CopyPatterntoTemp() 
{
    copy(pattern.begin(),pattern.end(),back_inserter(tempPattern));
    reverse(tempPattern.begin(),tempPattern.end());/* Reverses the tempPattern */
}

/*****
 * Primary control loop for this controller object. This function will execute
 * the CPFA logic using the CPFA enumeration flag once per frame.
 *****/
void iAnt_controller::ControlStep() {

    if(Stop())
    {
        return;
    }

    if(isHoldingFood == false) {
        /* draws target rays every 2 seconds */
        if((data->DrawTargetRays < 4) && (data->SimTime % (data->TicksPerSecond * 2)) == 0 ) {
            CVector3 position3d(GetPosition().GetX(), GetPosition().GetY(), 0.02);
            CVector3 target3d(GetTarget().GetX(), GetTarget().GetY(), 0.02);
            CRay3 targetRay(target3d, position3d);
            data->TargetRayList.push_back(targetRay);
        }
    }

    /* Checks if the robot found a food */
    SetHoldingFood();

    /* If it didn't continue in a sprial */
    if(IsHoldingFood() == false){
       GetTargets(); /* Initializes targets positions. */

    } else { /* Check if it is near the nest then set isHoldingFood to false */
        if((GetPosition() - data->NestPosition).SquareLength() < data->NestRadiusSquared) {
            isHoldingFood = false;
        } else {
            ApproachTheTarget(data->NestPosition);
        }
    }
}   

/*****
 *
 *****/
CRadians iAnt_controller::GetCollisionHeading() {

    typedef const CCI_FootBotProximitySensor::TReadings PR;
    PR &proximityReadings = proximitySensor->GetReadings();
    size_t collisionsDetected = 0;
    CRadians angle;

    for(size_t i = 0; i < proximityReadings.size(); i++) {
        if(proximityReadings[i].Value == 0.0) {
            angle += proximityReadings[i].Angle;
        }
    }

    return angle;
}

/*****
 *
 *****/
bool iAnt_controller::IsCollisionDetected() {
    //MODIFY COLLISION DECTECTION HERE.
   
    typedef const CCI_FootBotProximitySensor::TReadings PR;
    PR &proximityReadings = proximitySensor->GetReadings();
    size_t collisionsDetected = 0;
    CRadians angle;

    for(size_t i = 0; i < proximityReadings.size(); i++) {
        angle = proximityReadings[i].Angle;

        if((proximityReadings[i].Value > 0.0) &&
           (AngleToleranceInRadians.WithinMinBoundIncludedMaxBoundIncluded(angle))) {
            collisionsDetected++;
        }
    }

    return (collisionsDetected > 0) ? (true) : (false);

   //THIS IS CODE FROM DIFFUSION EXAMPLE IN ARGOS 
   /* Get readings from proximity sensor */
   // const CCI_FootBotProximitySensor::TReadings& tProxReads = proximitySensor->GetReadings();
   // /* Sum them together */
   // CVector2 cAccumulator;
   // size_t collisionsDetected = 0;
   // Real m_fDelta = 0.25;

   // for(size_t i = 0; i < tProxReads.size(); ++i) {
   //    cAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);

   //    if(tProxReads[i].Value > 0.0) collisionsDetected++;
   // }
   
   // cAccumulator /= tProxReads.size();
   // /* If the angle of the vector is small enough and the closest obstacle
   //  * is far enough, continue going straight, otherwise curve a little
   //  */
   // CRadians cAngle = cAccumulator.Angle();

   // if(AngleToleranceInRadians.WithinMinBoundIncludedMaxBoundIncluded(cAngle) &&
   //    cAccumulator.Length() < m_fDelta ) {
   //    /* Go straight */
   //    motorActuator->SetLinearVelocity(RobotForwardSpeed, RobotForwardSpeed);
   // }
   // else {
   //    /* Turn, depending on the sign of the angle */
   //    if(cAngle.GetValue() > 0.0f) {
   //       motorActuator->SetLinearVelocity(RobotTurningSpeed, -RobotTurningSpeed);
   //    }
   //    else {
   //       motorActuator->SetLinearVelocity(-RobotTurningSpeed, RobotForwardSpeed);
   //    }
   // }

   //  return (collisionsDetected > 0) ? (true) : (false);
}

/*****
 * Sets target North of the robot's current target.
 *****/
void iAnt_controller::SetTargetN(char x){
    CVector2 position = GetTarget();
    target = CVector2(position.GetX()+stepSize,position.GetY());
}

/*****
 * Sets target South of the robot's current target.
 *****/
void iAnt_controller::SetTargetS(char x){
    CVector2 position = GetTarget();
    target = CVector2(position.GetX()-stepSize,position.GetY());
}

/*****
 * Sets target East of the robot's current target.
 *****/
void iAnt_controller::SetTargetE(char x){
   CVector2 position = GetTarget();
   target = CVector2(position.GetX(),position.GetY()-stepSize);
}

/*****
 * Sets target West of the robot's current target.
 *****/
void iAnt_controller::SetTargetW(char x){
    CVector2 position = GetTarget();
    target = CVector2(position.GetX(),position.GetY()+stepSize);
}

/*****
 * Controls the robot's motor to go in the correct angle relative to the target.
 *****/
void iAnt_controller::ApproachTheTarget(){

    /* angle of the robot's direction relative to the arena's origin */
    CRadians angle1  = GetHeading();

    /* angle from the target to the robot's position */
    CRadians angle2  = (target - GetPosition()).Angle();

    /* heading = angle1 - angle2 = 0.0 when the robot is facing its target */
    CRadians heading = (angle1 - angle2).SignedNormalize();

    //UDPDATED TO ACCOMADATE THE DIFFUSION COLLSION AVOIDANCE
    // if(IsCollisionDetected() == false) 
    // {  
        
    //     if(heading <= AngleToleranceInRadians.GetMin()) {
    //         /* turn left */
    //         motorActuator->SetLinearVelocity(-RobotTurningSpeed, 
    //                                           RobotTurningSpeed);
    //     } else if(heading >= AngleToleranceInRadians.GetMax()){
    //         /* turn right */
    //         motorActuator->SetLinearVelocity( RobotTurningSpeed, 
    //                                          -RobotTurningSpeed);
    //     } else {
    //         /* go straight */
    //         motorActuator->SetLinearVelocity(RobotForwardSpeed, 
    //                                          RobotForwardSpeed);
    //     }

    // }
    if(heading <= AngleToleranceInRadians.GetMin()) {
        /* turn left */
        motorActuator->SetLinearVelocity(-RobotTurningSpeed, 
                                          RobotTurningSpeed);
    } else if(heading >= AngleToleranceInRadians.GetMax()){
        /* turn right */
        motorActuator->SetLinearVelocity( RobotTurningSpeed, 
                                         -RobotTurningSpeed);
    } else {
        /* go straight */
        motorActuator->SetLinearVelocity(RobotForwardSpeed, 
                                         RobotForwardSpeed);
    }
}

void iAnt_controller::ApproachTheTarget(CVector2 myTarget){

    /* angle of the robot's direction relative to the arena's origin */
    CRadians angle1  = GetHeading();

    /* angle from the target to the robot's position */
    CRadians angle2  = (myTarget - GetPosition()).Angle();

    /* heading = angle1 - angle2 = 0.0 when the robot is facing its target */
    CRadians heading = (angle1 - angle2).SignedNormalize();

    if(heading <= AngleToleranceInRadians.GetMin()) {
        /* turn left */
        motorActuator->SetLinearVelocity(-RobotTurningSpeed, 
                                          RobotTurningSpeed);
    } else if(heading >= AngleToleranceInRadians.GetMax()){
        /* turn right */
        motorActuator->SetLinearVelocity( RobotTurningSpeed, 
                                         -RobotTurningSpeed);
    } else {
        /* go straight */
        motorActuator->SetLinearVelocity(RobotForwardSpeed, 
                                         RobotForwardSpeed);
    }
}
/*****
 *
 *****/
CVector2 iAnt_controller::GetTarget() {
    return target;
}

/*****
 * Helper function that reads vector <char> pattern
 * and sets the target's direction base on the 
 * char at the current vector index.
 *****/
 void iAnt_controller::GetTargets(){

    /* Finds the last direction of the pattern. */
    char direction_last = tempPattern[tempPattern.size() - 1]; 
   
    /* If the robot hit target and the patter size >0
       then find the next direction. */
    if(TargetHit() == true && tempPattern.size() > 0) {
        tempPattern.pop_back();

        switch(direction_last)
        {
            case 'N':
                SetTargetN('N');
                break;
            case 'S':
                SetTargetS('S');
                break;
            case 'E':
                SetTargetE('E');
                break;
            case 'W':
                SetTargetW('W');
                break;
            default:
                motorActuator->SetLinearVelocity(0.0, 0.0);        
        }
    }
    /* If the robot is down traversing the tempPattern, then return home */
    else if(tempPattern.size() == 0){
        ApproachTheTarget(data->NestPosition);
        Reset();
    /* Otherwise we continue to approach the target. */  
    } else ApproachTheTarget();
 }

/*****
 * Returns a boolean based on weather the robot is with 0.01 
 * distance tolerance. Declares that the robot had reached 
 * current target.
 *****/
 bool iAnt_controller::TargetHit(){
    CVector2 position = GetPosition();
    bool hit = false;
     
    if((position-target).SquareLength() < 0.01){
        hit = true;
    }
    return hit;
 }

/*****
 * Check if the iAnt is finding food. This is defined as the iAnt being within
 * the distance tolerance of the position of a food item. If the iAnt has found
 * food then the appropriate boolean flags are triggered.
 *****/
void iAnt_controller::SetHoldingFood(){
    /* Is the iAnt already holding food? */
    if(IsHoldingFood() == false) {
        vector <CVector2> newFoodList; 
        size_t i = 0; 

        /* No, the iAnt isn't holding food. Check if we have found food at our
           current position and update the food list if we have. */

        for (i = 0; i < data->FoodList.size(); i++){
            /* We found food! */
            if ((GetPosition()-data->FoodList[i]).SquareLength() < data->FoodRadiusSquared){
                isHoldingFood = true;
                //goingHome = true;
            }
            /* Else push the that current food onto the newFoodList. */
            else {
                /* Return this unfound-food position to the list */
                newFoodList.push_back(data->FoodList[i]);
            }
        } 
        data->FoodList = newFoodList;
    }
}
/*****
 * Is this iAnt_controller holding food?
 *     true  = yes
 *     false = no
 *****/
bool iAnt_controller::IsHoldingFood() {
    return isHoldingFood;
}
/*****
 * After pressing the reset button in the GUI, this controller will be set to
 * default factory settings like at the start of a simulation.
 *****/
void iAnt_controller::Reset() {
    collisionDelay  = 0;
    target          = data->NestPosition;
    tempPattern.clear();
    CopyPatterntoTemp();
    //goingHome = false;

}

/*****
 * iAnt_loop_functions uses this function to set the iAnt_data pointer.
 *****/
void iAnt_controller::SetData(iAnt_data* dataPointer) {
    data = dataPointer;
}

/*****
 * iAnt_qt_user_functions uses this function to get the iAnt_data pointer.
 *****/
iAnt_data* iAnt_controller::GetData() {
    return data;
}

/*****
 * Return the robot's 2D position on the arena.
 *****/
CVector2 iAnt_controller::GetPosition() {
    /* The robot's compass sensor gives us a 3D position. */
    CVector3 position3D = compass->GetReading().Position;
    /* Return the 2D position components of the compass sensor reading. */
    return CVector2(position3D.GetX(), position3D.GetY());
}

CVector3 iAnt_controller::GetStartPosition() 
{ 
    return startPosition; 
}

/*****
 * Return the angle the robot is facing relative to the arena's origin.
 *****/
CRadians iAnt_controller::GetHeading() {
    /* in ARGoS, the robot's orientation is represented by a quaternion */
    const CCI_PositioningSensor::SReading& sReading = compass->GetReading();
    CQuaternion orientation = sReading.Orientation;

    /* convert the quaternion to euler angles */
    CRadians z_angle, y_angle, x_angle;
    orientation.ToEulerAngles(z_angle, y_angle, x_angle);

    /* the angle to the z-axis represents the compass heading */
    return z_angle;
}

REGISTER_CONTROLLER(iAnt_controller, "iAnt_controller")
