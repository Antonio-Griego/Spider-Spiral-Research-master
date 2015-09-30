function paths = plotSpiral( N_circuits, N_robots )
% This function plots the spiral paths of N robots for N circuits.
% N_circuits - the number of circuits to plot. Where a circuit is defined
% as the part of the spiral that is one rotation around the center ....
% N_robots - the number of robots
% Authors: Linh Tran, Matthew Fricke
% Date: 8/11/15

for i= 1:N_robots
    paths_x{i} = 0;
    paths_y{i} = 0;
    jth_paths{i} = '';
end


for i_robot = 1:N_robots
    
    for i_circuit = 0:N_circuits
        
        n_steps_north = calcDistanceToTravel( i_robot, i_circuit, N_robots, 'N')
        
        for j = 1:n_steps_north
            
            paths_x{i_robot} = [ paths_x{i_robot}; paths_x{i_robot}(end)+0 ];
            paths_y{i_robot} = [ paths_y{i_robot}; paths_y{i_robot}(end)+1 ];
            jth_paths{i_robot} = [jth_paths{i_robot},createPathString('N')]
        end
        
%             disp(['Robot number ' num2str(i_robot) ' went ' num2str(n_steps_north) ' steps North on circuit ' num2str(i_circuit)]);
       
        
        n_steps_east = calcDistanceToTravel( i_robot, i_circuit, N_robots, 'E')
        
        for j = 1:n_steps_east
            paths_x{i_robot} = [ paths_x{i_robot}; paths_x{i_robot}(end)+1 ];
            paths_y{i_robot} = [ paths_y{i_robot}; paths_y{i_robot}(end)+0 ];
            jth_paths{i_robot} = [jth_paths{i_robot},createPathString('E')]
        end
       
%             disp(['Robot number ' num2str(i_robot) ' went ' num2str(n_steps_east) ' steps East on circuit ' num2str(i_circuit)]);
        
        n_steps_south = calcDistanceToTravel( i_robot, i_circuit, N_robots, 'S' );
        
        for j = 1:n_steps_south
            paths_x{i_robot} = [ paths_x{i_robot}; paths_x{i_robot}(end)+0 ];
            paths_y{i_robot} = [ paths_y{i_robot}; paths_y{i_robot}(end)-1 ];
            jth_paths{i_robot} = [jth_paths{i_robot},createPathString('S')]
        end
        
%             disp(['Robot number ' num2str(i_robot) ' went ' num2str(n_steps_south) ' steps South on circuit ' num2str(i_circuit)]);
        
        n_steps_west = calcDistanceToTravel( i_robot, i_circuit, N_robots, 'W')
        
        for j = 1:n_steps_west
            paths_x{i_robot} = [ paths_x{i_robot}; paths_x{i_robot}(end)-1 ];
            paths_y{i_robot} = [ paths_y{i_robot}; paths_y{i_robot}(end)+0 ];
            jth_paths{i_robot} = [jth_paths{i_robot},createPathString('W')]
        end
        
%             disp(['Robot number ' num2str(i_robot) ' went ' num2str(n_steps_west) ' steps West on circuit ' num2str(i_circuit)]);
    end
end

paths = [paths_x; paths_y]';
writePaths(jth_paths,N_robots);

end

