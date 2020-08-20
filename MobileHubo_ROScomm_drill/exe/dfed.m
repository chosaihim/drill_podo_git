data = load('data.txt');

WSTref = data(:,1);
RSRref = data(:,3);

WSTenpos = data(:,16);
WSTenref = data(:,17);

RSRenpos = data(:,18);
RSRenref = data(:,19);

JOG = data(:,20);

WBdesRHy = data(:,21);
WBdesRELB = data(:,22);
WBpRHy = data(:,23);
WBpRELB = data(:,24);

WSTjoref = data(:,25);
RSRjoref = data(:,26);

rwWST = data(:,27);
joWST = data(:,28);
wrWST = data(:,29);
this = data(:,30);

figure
hold on;
plot(WSTref);
plot(WSTenpos);
plot(WSTenref);
plot(WSTjoref);
plot(JOG*0.0001);
legend('ref','enpos','enref','joref','jog','this');

figure
hold on;
plot(WBdesRELB);
plot(WBpRELB);
plot(WSTjoref);
legend('des','p','k');

figure
hold on;
plot(rwWST);
plot(joWST);
plot(wrWST);
plot(this);
legend('rw','jo','wr','this');