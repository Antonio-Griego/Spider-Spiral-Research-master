function n_steps = calcDistanceToTravel( i_robot, i_circuit, N_robots, direction )
% Recursive helper function to calculate part of a spiral. To be called by the
% plotSpiral function.
% Plots the movement of a robot given a direction. Calculates how far to go
% in that direction
% directions: ENS or W.
% n_circuit - number of total circuits to plot
% i_circuit - number of the current circuit
% i_robot - which robot are we (between 1 and N_robots
% N_robots - the total number of robots
% n_steps - return the number of steps to go in the direction given
% Authors: Linh Tran, Matthew Fricke
% Date: 8/11/15

i = i_robot;
j = i_circuit;
N = N_robots;
    
if direction == 'N' || direction == 'E'    
  if j == 0
      n_steps = i_robot;
      return;
  elseif j==1
      n_steps = calcDistanceToTravel(i,j-1,N,direction)+i+N;
      return;
  else
      n_steps = calcDistanceToTravel(i,j-1,N,direction)+2*N;
  end
  
elseif direction == 'S' || direction == 'W'
    if j == 0
        n_steps = calcDistanceToTravel( i, j, N, 'N' ) + i;
        return;
    elseif j > 0
        n_steps = calcDistanceToTravel( i, j, N, 'N' ) + N;
        return;
    end
else
    disp(['Error direction ' direction ' is invalid.']);
end

end

