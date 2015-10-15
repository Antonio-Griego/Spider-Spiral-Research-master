% This file works in unison with the dataRead.m file to import data
% from multiple text files into matlab while ploting a the mean and 
% std of both the CPFA vs. the DSA Search. This code will generate
% a graph of 5 subplots on a 3x2 grid. Use it by calling plotCPFAdata.
% 07/08/15
% Where dataRead is being called.

%read in the data for CPFA
[meanData60R,stdData60R]= dataRead('iAntTagData60R.txt');
[meanData50R,stdData50R]= dataRead('iAntTagData50R.txt');
[meanData40R,stdData40R]= dataRead('iAntTagData40R.txt');
[meanData30R,stdData30R]= dataRead('iAntTagData30R.txt');
[meanData20R,stdData20R]= dataRead('iAntTagData20R.txt');
[meanData10R,stdData10R]= dataRead('iAntTagData10R.txt');

[meanData60C,stdData60C]= dataRead('iAntTagData60C.txt');
[meanData50C,stdData50C]= dataRead('iAntTagData50C.txt');
[meanData40C,stdData40C]= dataRead('iAntTagData40C.txt');
[meanData30C,stdData30C]= dataRead('iAntTagData30C.txt');
[meanData20C,stdData20C]= dataRead('iAntTagData20C.txt');
[meanData10C,stdData10C]= dataRead('iAntTagData10C.txt');

[meanData60P,stdData60P]= dataRead('iAntTagData60P.txt');
[meanData50P,stdData50P]= dataRead('iAntTagData50P.txt');
[meanData40P,stdData40P]= dataRead('iAntTagData40P.txt');
[meanData30P,stdData30P]= dataRead('iAntTagData30P.txt');
[meanData20P,stdData20P]= dataRead('iAntTagData20P.txt');
[meanData10P,stdData10P]= dataRead('iAntTagData10P.txt');

%read in data for DSA
[meanData60SR,stdData60SR]= dataRead('iAntSpiralTagData60R.txt');
[meanData50SR,stdData50SR]= dataRead('iAntSpiralTagData50R.txt');
[meanData40SR,stdData40SR]= dataRead('iAntSpiralTagData40R.txt');
[meanData30SR,stdData30SR]= dataRead('iAntSpiralTagData30R.txt');
[meanData20SR,stdData20SR]= dataRead('iAntSpiralTagData20R.txt');
[meanData10SR,stdData10SR]= dataRead('iAntSpiralTagData10R.txt');

[meanData60SC,stdData60SC]= dataRead('iAntSpiralTagData60C.txt');
[meanData50SC,stdData50SC]= dataRead('iAntSpiralTagData50C.txt');
[meanData40SC,stdData40SC]= dataRead('iAntSpiralTagData40C.txt');
[meanData30SC,stdData30SC]= dataRead('iAntSpiralTagData30C.txt');
[meanData20SC,stdData20SC]= dataRead('iAntSpiralTagData20C.txt');
[meanData10SC,stdData10SC]= dataRead('iAntSpiralTagData10C.txt');

[meanData60SP,stdData60SP]= dataRead('iAntSpiralTagData60P.txt');
[meanData50SP,stdData50SP]= dataRead('iAntSpiralTagData50P.txt');
[meanData40SP,stdData40SP]= dataRead('iAntSpiralTagData40P.txt');
[meanData30SP,stdData30SP]= dataRead('iAntSpiralTagData30P.txt');
[meanData20SP,stdData20SP]= dataRead('iAntSpiralTagData20P.txt');
[meanData10SP,stdData10SP]= dataRead('iAntSpiralTagData10P.txt');

%Plot using subplot

%Random CPFA vs. DSA Search
figure
subplot(1,3,1)
hold on
x = 0:10:60;

y = [0,meanData10R,meanData20R,meanData30R,meanData40R,meanData50R,meanData60R];
y2 =[0,meanData10SR,meanData20SR,meanData30SR,meanData40SR,meanData50SR,meanData60SR];

e = [0,stdData10R,stdData20R,stdData30R,stdData40R,stdData50R,stdData60R];
e2 = [0,stdData10SR,stdData20SR,stdData30SR,stdData40SR,stdData50SR,stdData60SR];
errorbar(x,y,e, 'b-');
errorbar(x,y2,e2, 'r-');
axis([-1 61 0 200]);
title('Random Data','fontsize',20);
legend('CFPA','DSA','fontsize',20);
xlabel('Time in Minutes','fontsize',18);
ylabel('# of Tags Collected','fontsize',18);
hold off

%Calculate Random perecent difference of CPFA vs. DSA
R = calcPercentDiff(y(7),y2(7));

%Cluster CPFA vs. DSA Search
subplot(1,3,2)
hold on
x = 0:10:60;

y = [0,meanData10C,meanData20C,meanData30C,meanData40C,meanData50C,meanData60C];
y2 =[0,meanData10SC,meanData20SC,meanData30SC,meanData40SC,meanData50SC,meanData60SC];

e = [0,stdData10C,stdData20C,stdData30C,stdData40C,stdData50C,stdData60C];
e2 =[0,stdData10SC,stdData20SC,stdData30SC,stdData40SC,stdData50SC,stdData60SC];

errorbar(x,y,e, 'b-');
errorbar(x,y2,e2, 'r-');
axis([-1 61 0 200]);
title('Cluster Data','fontsize',20);
hold off

C = calcPercentDiff(y(7),y2(7));

%Power Law CPFA vs. DSA Search 
subplot(1,3,3)
hold on
x = 0:10:60;
y = [0,meanData10P,meanData20P,meanData30P,meanData40P,meanData50P,meanData60P];
y2 =[0,meanData10SP,meanData20SP,meanData30SP,meanData40SP,meanData50SP,meanData60SP];

e = [0,stdData10P,stdData20P,stdData30P,stdData40P,stdData50P,stdData60P];
e2 =[0,stdData10SP,stdData20SP,stdData30SP,stdData40SP,stdData50SP,stdData60SP];

errorbar(x,y,e, 'b-');
errorbar(x,y2,e2, 'r-');
axis([-1 61 0 200]);
title('Power Law Data','fontsize',20);
hold off

P = calcPercentDiff(y(7),y2(7));

%Plot bar graph of 3 average percentage difference CPFA vs. DSA
figure();
bar(1,R,'r');
hold on
bar(2,C,'g');
bar(3,P,'b');
Labels = {'Random', 'Cluster', 'Power'};
set(gca, 'XTick', 1:3, 'XTickLabel', Labels, 'fontsize',20);
title('DSA vs. CPFA Efficency','fontsize',25);
xlabel('Type of Food Distribution','fontsize',20);
ylabel('% Avg of Improvement','fontsize',20);

strR = {R};
annotation('textbox',[0.180,0.740,0.1,0.1],'String',strR, 'fontsize',20);
strC = {C};
annotation('textbox',[0.435,0.255,0.1,0.1],'String',strC,'fontsize',20);
strP = {P}
annotation('textbox',[0.690,0.285,0.1,0.1],'String',strP,'fontsize',20);

