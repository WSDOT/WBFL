# Tasks {#tasks}
The WBFL DManip framework performs complex tasks by executing Task objects. The design of the task management system is based on a paper title [Taskmaster: An Architecture Pattern for GUI Applications](..\..\..\Supporting Documents\taskmaster.pdf) by Robert Martin, James Newkirk, and Bhama Rao.

# Standard Tasks
The standard tasks supported by the framework are

Task | Description
-----|-------------------------------------------------------------------------------
Inplace Edit Task      | Manages inplace editing 
RectSelect Task        | Manages mouse operations for selecting display objects by drawing a rectangle 
Local Drag Drop Task   | Manages drag and drop that occurs within a Display View 
Foreign Drag Drop Task | Manages drag and drop that begins outside of a Display View 
Center On Point Tasks  | Manages mouse operations for centering the world space on a device point 
Zoom Task              | Manages mouse operations for zooming by drawing a rectangle 

# User Defined Tasks
You can create your own tasks by defining a task-specific interface along with its implementation, building an appropriate finite state machine, extending the task factory, and implementing a trigger for the task.

A trigger is simply a user action that begins the task. For example, a task might start with the user right clicks the mouse button over a display object. You would respond to this event by creating the appropriate task object and handing it off to the Display Manager. The Display Manager will direct all user interactions to the task object until the task is complete. Tasks can also be triggered by pressing toolbar buttons or selecting menu commands.
