function writePaths (jth_paths, N_robots, N_circuits)
    
    path = '/Users/linhtran/Desktop/iAnt-ARGoS-linh_development/';
    fid = fopen([path,'sample.txt'],'w');
    for i = 1:N_robots;
        fprintf(fid,jth_paths{i});
        fprintf(fid,'\n');
%         fprintf(fid, jth_paths{i});
    end
%     fprintf(fid,[int2str(N_robots),':',int2str(N_circuits)],'\n');
    fclose(fid);
end