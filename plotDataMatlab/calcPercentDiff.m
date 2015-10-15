%Calculates the percentage of impovement of y to x.
% y = DSA
% x = CPFA
% formula = (DSA - CPFA)/CFPA
% Avg % of improvement of DSA to CPFA.
function pctDiff = calcPercentDiff(x,y)
    elemDiff = (y-x);
    pctDiff = 100*((elemDiff)./(x));
end