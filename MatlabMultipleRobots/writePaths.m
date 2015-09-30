function writePaths (jth_paths, N_robots)
    
    path = '/Users/linhtran/Desktop/';
    fid = fopen([path,'sample1.txt'],'w');
    for i = 1:N_robots;
        s1 = 'R';
        s2 = int2str(i);
        s = [s1 s2];
        fprintf(fid,s);
        fprintf(fid,jth_paths{i});
%         fprintf(fid, jth_paths{i});
    end
    fclose(fid);
end