# Timer-with-Arduino-and-rotary-encoder-2
This timer has the same hardware structure as Timer-with-Arduino-and-rotary-encoder-1.
Different soft structure.
The time is displayed in the format hh mm ss.
Maximum time is 99h 59m 59 s.
Programming: Set number seconds (rotary encoder) - push - secondsX10 - push -  minutes- push - minutesX10-push-hours-push-hoursX10. Now the time is set. The next push will trigger the delay.

During the time delay the load will be powered through the Rel relay. If the MEM button is pressed, no further programming is required, the previous value is retained.
