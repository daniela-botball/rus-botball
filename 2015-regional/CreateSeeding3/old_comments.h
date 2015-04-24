// Created on Tue April 21 2015

// Replace FILE with your file's name
#ifndef _FILE_H_
#define _FILE_H_

// COMMENTS after Thursday 4/16 session:
//   -- Scores all 5, but have yet to get all 5 in a single run.
//   -- Winch has occasionally gone down completely wrong for the first pickup.  Disaster.  Easily fixed, IMO.
//   -- Scoring first 2 cubes was mostly reliable except:
//       -- Winch sometimes failed completely on first pickup.
//       -- Placement of cubes is important.
//       -- The fingers sometimes grab too high.  Either add lower fingers or ???
//       -- (Good that) The drop always worked.
//       -- (Good that) it is only 16 seconds.
//          However, it could easily be made faster without any loss in reliability.  Maybe important for double elimination.
//   -- For picking up the next 2 cubes:
//        -- IMO the path to get ready for the second pickup wastes a lot of time and is still not 100% reliable.
//        -- Even small errors cause failure either in the claw grabbing a pole (maybe should close, then later open, the claw?)
//           or (more typically) in not being in EXACTLY the right position for the pickup.
//        -- I looked at the camera with a pink model.  It did fine in saying where to go.
//           I strongly suspect that the camera is needed for the last little bit.
//        -- In any case, the motions after the robot has hit (and squared up on) the Cave PVC need to be reworked to work better
//           to cover unavoidable variations in position at that point.
//   -- Dropping the next 2 cubes is very practical but not fully tuned yet.
//        -- Using the camera or some sensor may help.
//        -- It is practical to score the 5th cube on the way to dropping cubes 3 and 4.
//   -- Timing is roughly:
//       -- 16 seconds to drop first 2 cubes
//       -- 25 more seconds to reach the opposite side (it would be more if the big-run speed were still at 20, I bumped it to 100)
//       -- 20 more seconds to grab the next 2 cubes
//       -- 20 more seconds to drop the last 2 cubes and also knock in the 5th cube on the way
//      So about 1 minutes and 20 seconds to that point.  That is good news!

// TODO: (talk to your coach about EACH of these before doing them)
//  Learn and practice the new   adjust   function.
//  Put comments in   score_our_cubes   for each major action (which will be a chunk of code).
//  Continue pushing actions forward:
//    -- Score 2 cubes on our starting zone line
//    -- Score 2 cubes on opponent's starting zone line
//    -- Score cube and two poms on Mesa.
//    -- Then ??
//  The library should allow the Create to specify either side as the "front".
// Failure points to check:
//  servo extender wire coming disconnected.
//  fishing wire getting too loose or tangled or off the winch.

/*
Create score the last 3 cubes.
Aaron will make mechanical changes Saturday.
Lego robot -- push it forward.
*/

#endif
