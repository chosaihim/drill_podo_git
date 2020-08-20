clear
clc
data = load('data123123555.txt');

startT = 24;
stopT = 1476;
time = startT:1:stopT;

RWHv = data(:,2);
LWHv = data(:,3);
BWHv = data(:,4);

RWHp = data(:,8);
LWHp = data(:,9);
BWHp = data(:,10);

Px = data(time,14);
Py = data(time,15);
Pth = data(time,16);

Vx = data(time,17);
Vy = data(time,18);
Vth = data(time,19);

InputY = data(time,20);

Tcur = data(time,21);
Tgoal = data(time,22);
Tsat = data(time,23);

Pyy(1) = 0;
Pxx(1) = 0;
for i=2:1:1453
   Pyy(i) = Pyy(i-1) + Vy(i)*0.005;
   Pxx(i) = Pxx(i-1) + Vx(i)*0.005;
end
figure
hold on;
plot(Vx);
plot(Vy);
plot(InputY);
plot(Px);
plot(Pyy);
legend('Vx','Vy','In','Px','Py')

figure
hold on;
plot(Px,Pyy);
axis('equal')

figure
hold on;
plot(RWHv);
plot(LWHv);
plot(BWHv);
legend('r','l','b')