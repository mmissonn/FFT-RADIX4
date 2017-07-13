% programme qui trace la courbe d'un signal complexe 
% partie reele contenue dans fft_re. format ASCII 
% partie imaginaire contenue dans fft_ima.
N=256

%load fft_pol.
load fai_re.
load fai_ima.
load faii_re.
load faii_ima.
load fb_re.
load fb_ima.
load fc_re.
load fc_ima.



F1= fai_re + fai_ima * i;
F2= faii_re + faii_ima * i;
F3= fb_re + fb_ima * i;
F4= fc_re + fc_ima * i;



t=0:1:N-1;
f1=cos(2*pi*t/N*9);
f2=cos(2*pi*t/N*9.5);
f3=t.*exp(-.1*t);
f4=exp(.05*t);

Z1=fft(f1);
Z2=fft(f2);
Z3=fft(f3);
Z4=fft(f4);



clg;

%plot(t,f,'+')
%pause




%subplot(121), plot(Z,'*'), title('FFT Matlab'), 
%subplot(122), plot(F,'+'), title('FFT radix4'), 
%pause

clg

w=(0:N-1);

% magnitude du signal
subplot(122), plot(w, sqrt( (real(Z1).*real(Z1)) + (imag(Z1).*imag(Z1)) )) , 
title('Amplitude Matlab #1'),
subplot(121), plot(w, sqrt( (real(F1).*real(F1)) + (imag(F1).*imag(F1)) )),
title('Amplitude Radix4 #1'),

pause
clg

% phase du signal
subplot(122), plot(w, atan(imag(Z1)./real(Z1))),
title('Phase Matlab #1'),
subplot(121), plot(w, atan(imag(F1)./real(F1))),
title('Phase Radix4 #1'),

pause
clg

%***************************************************************

% magnitude du signal
subplot(122), plot(w, sqrt( (real(Z2).*real(Z2)) + (imag(Z2).*imag(Z2)) )) ,
title('Amplitude Matlab #2'),
subplot(121), plot(w, sqrt( (real(F2).*real(F2)) + (imag(F2).*imag(F2)) )) ,
title('Amplitude Radix4 #2'),

pause
clg

% phase du signal
subplot(122), plot(w, atan(imag(Z2)./real(Z2))),
title('Phase Matlab #2'),
subplot(121), plot(w, atan(imag(F2)./real(F2))),
title('Phase Radix4 #2'),

pause
clg

%***************************************************************


% magnitude du signal
subplot(122), plot(w, sqrt( (real(Z3).*real(Z3)) + (imag(Z3).*imag(Z3)) )) ,
title('Amplitude Matlab #3'),
subplot(121), plot(w, sqrt( (real(F3).*real(F3)) + (imag(F3).*imag(F3)) )) ,
title('Amplitude Radix4 #3'),


pause
clg

% phase du signal
subplot(122), plot(w, atan(imag(Z3)./real(Z3))),
title('Phase Matlab #3'),
subplot(121), plot(w, atan(imag(F3)./real(F3))),
title('Phase Radix4 #3'),

pause
clg

%***************************************************************


% magnitude du signal
subplot(122), plot(w, sqrt( (real(Z4).*real(Z4)) + (imag(Z4).*imag(Z4)) )) ,
title('Amplitude Matlab #4'),
subplot(121), plot(w, sqrt( (real(F4).*real(F4)) + (imag(F4).*imag(F4)) )) ,
title('Amplitude Radix4 #4'),


pause
clg

% phase du signal
subplot(122), plot(w, atan(imag(Z4)./real(Z4))),
title('Phase Matlab #4'),
subplot(121), plot(w, atan(imag(F4)./real(F4))),
title('Phase Radix4 #4'),

pause
