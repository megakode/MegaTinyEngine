Actions:

     * Transformation Actions: Move, Rotate, Scale, Fade, Tint, etc.
     * Composable actions: Sequence, Spawn, Repeat, Reverse
     * Ease Actions: Exp, Sin, Cubic, Elastic, etc.
     * Misc actions: CallFunc, OrbitCamera, Follow, Tween
     
Action:
tartWithTarget(Node *aTarget)
 step(float /*dt*/)   
 update(float /*time*/)   
 isDone
 stop
FiniteTimeAction : Action
 getDuration()
 setDuration
 reverse
 
 Every action has a step and an update function. 
 Step is called every frame with the delta time 
 Update is called every frame with a value between 0 and 1 (which is the normalized time of the action)
 
 For all ActionInterval based actions (of which, MoveBy and Sequence are), 
 most DO NOT override the step function - instead ActionInterval::step is used
 ActionInterval::step calls the update function
 Container actions like Sequence and Spawn call their internal actions’ 
 update function from their own update function 
 ActionInterval::step increments an _elapsed variable, 
 which is used in isDone to test if the action is complete
 
 ----------------
 
 Thinking of implementing the API like this:
 
 // Seriel sequence
 sprite.addAction( FadeAction.create(.200f) + MoveAction.create({100,-50}) );
 
 // Parallel sequence
 sprite.addAction( FadeAction.create(.200f) );
 sprite.addAction( MoveAction.create({100,-50}) );
