##Lab 05 - Results Analysis

##sheet:https://docs.google.com/spreadsheets/d/14pJGpZHGnGALFc_r7dXQ96MqV859bouMK1cTi6eMV00/edit?usp=sharing
##all raw terminal output is inside results.txt

**What the results actually show**

Looking at the numbers from size 2^10 up to 2^16, here is basically what happened:

 -standard double starts messing up pretty fast as the array gets bigger.
 at 2^10 elements the error is already around 7.10e-15, but by 2^16 it jumps all the way to 5.63e-10.
 this shows how normal float addition drops tiny digits when you keep adding numbers over and over.
 -long double and pairwise both fixed the error completely, showing 0.00e+00 all the way through.
 -pairwise was super fast too (only 0.000046 s for 65k elements).
 since pairwise adds numbers in small balanced groups, it avoids precision loss without making the cpu do extra work.
 -kahan and knuth also completely got rid of the error, but they take more time to run.
 at 2^16 elements, kahan took 0.000269 s and knuth took 0.000100 s.
 this makes sense because both algorithms have to do extra math operations in every loop iteration just to keep track of the dropped bits.

**Quick summary**

 -normal double is fine for the small stuff, but bad when you have big arrays and need precision. 
 -pairwise is basically it gives zero error and runs fast.
 - kahan and khnut are very accurate, but you pay a speed penalty for the extra error tracking math. 
