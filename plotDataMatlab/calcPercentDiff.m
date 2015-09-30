function pctDiff = calcPercentDiff(x,y)
    elemDiff = (y-x);
    pctDiff = 100*((elemDiff)./(y));
end