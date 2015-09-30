function plotMultiplePatterns( paths )
% Wrapper function for plotPattern. Allows search patterns for multiple
% robots to be plotted. 
% A cell array containing vectors of coordinates. Each row contains two
% vectors corresponding to the path taken by a a robot. The ith row has 
% path coordinates for the ith robot. The first is X coordinates for a
% robot and the second is the Y coordinates.
%
% Breaks the cell array up into individual paths and passes them to
% plotPattern
% Author: Matthew Fricke
% Date: 8/12/15

hold on
grid on
for i = 1 : size(paths,1)

plotPattern(paths{i,1}, paths{i,2});

end

hold off

end

