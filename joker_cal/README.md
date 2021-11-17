# **Disclaimer**
I am by not means expert in neither mathimatics, C++ and speling. There are probably many mistakes in both the code and the math behind it. This is just a project I made for fun and learning. You have been advised... (passive-agressive)

# **Introduction**
This is a tool I created as practice for C++ and to prove that lottery is a waste of money, especially to my mother.

"Joker" is the name of the national lottery in Greece and Cyprus. `joker_cal` is a command line calculated applicationthat calculates how many draws will it take for you to reach a target percentage (i.e. 50%). This target percentage is the probability for you to win at least once. Addictionally, if you provide a jackpot and an estimation of the number of tickets being sold the expected value of the ticket will be calculated.

# **To Do...**
- [ ] Add on-screen option
- [ ] Implement taylor series approximation of log for analytical solution
- [ ] Try to add the extra cases in expected value (more guesses/varying cost)

# **Dependencies**
No dependancies, just download the binary and run it or the files from source.

# **Run**
To run the application open a terminal (i.e. Command Prompt) on the directory of the binaries and type:
```
> ./joker_cal <target-probability> <jackpot> <total-number-of-tickets> <options>
```
`<target-probability>` is the percentage in decimal format (i.e. 0.5 for 50%)
`<jackpot>` Optional. The value of the jackpot in euros.
`<total-number-of-tickets>` Optional. The estimate of the amount of ticket being sold.
`<options>` Currently not implemented. `-o` to display results results during the calculation process.

Alternatively, you can just run the binary (.exe) without any arguments and fill the answers in the program.

# **Details on Joker**
## **How to play**
To win the Jackpot in Joker you have to correctly guess 5 number from the first field and 1 from the second field. The first field contains 45 number and the second 20. You can select more than 5 number from the first field and more than 1 number in the second field, although you have to pay extra for each number. An online tool on the official website exist for calculating the cost. For simplicity we will not consider any of those cases. The standard fee for a ticket for 5+1 numbers is 0.5€.

## **Prize tiers**
Joker offers 8 prize tiers are available depending on how many correct guesses you made. All the tiers all listed below.

![Prize tiers](https://www.opap.gr/documents/63996/65648/deltio1EN.png/543afca2-ccfb-c6ed-1e58-07cebe74dc24?t=1508750210462&version=1.0)

The first 2 tiers prizes change depending on how many money has been accumulated from previous draws. Whenever there are no winners in any of the 2 tiers the sum is transfered to the next draw. The rest are fixed amounts.

# **How the tool works**
## **Target probability for at least 1 win**
Before we start we need to know what is the probability to win with a single guess. To find that we need to calculate the amount of possible combinations. This need to be done for each field seperately.

### **First field combinations**
We need to guess 5 numbers from a total of 45 numbers. So our first guess can be any of the 45. Since we already selected one and no repeat is allowed, for our second guess only 44 numbers are available. So for our 5-number guess we have:

![\begin{align*}
\color{red} \large
45\times44\times43\times42\times41=146611080
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0A45%5Ctimes44%5Ctimes43%5Ctimes42%5Ctimes41%3D146611080%0A%5Cend%7Balign%2A%7D%0A)

However, since the order of the number does not matter we need to divide that number with total number of possible permutations for 5 items. It can easily be proven that the number of permutions can be of 5 items is the factorial of 5:

![\begin{align*}
\color{red} \large
5!=5\times4\times3\times2\times1=120
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0A5%21%3D5%5Ctimes4%5Ctimes3%5Ctimes2%5Ctimes1%3D120%0A%5Cend%7Balign%2A%7D%0A)

So our final result for the first field is:

![\begin{align*}
\color{red} \large
\dfrac{146611080}{120}=1221759
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0A%5Cdfrac%7B146611080%7D%7B120%7D%3D1221759%0A%5Cend%7Balign%2A%7D%0A)

The above can be generalized in one equation for a field with ***n*** numbers and ***k*** choices with:

![\begin{align*}
\color{red} \large
{n \choose k}=\dfrac{n!}{k!(n-k)!} 
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0A%7Bn+%5Cchoose+k%7D%3D%5Cdfrac%7Bn%21%7D%7Bk%21%28n-k%29%21%7D+%0A%5Cend%7Balign%2A%7D%0A)

### **Second field combinatios and final probability for 1 ticket**
The second field is much simple. Since we are only selecting only one number out of 20 numbers, the amount of possible combinations are just 20. We can also verify that in the formula we derived previously with **n=20** and **k=1**. To combine the 2 field we simply multible the answers together since the independed from each other:

![\begin{align*}
\color{red} \large
C_{total}=1221759\times20=24435180
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0AC_%7Btotal%7D%3D1221759%5Ctimes20%3D24435180%0A%5Cend%7Balign%2A%7D%0A)

The final probability for winning with 1 guess is by definition the number of wanted outcomes divided by the total number of outcomes, which for out case is:

![\begin{align*}
\color{red} \large
P_{win}=\dfrac{1}{C_{total}}=\dfrac{1}{24435180}\approx4.09246013e-8
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0AP_%7Bwin%7D%3D%5Cdfrac%7B1%7D%7BC_%7Btotal%7D%7D%3D%5Cdfrac%7B1%7D%7B24435180%7D%5Capprox4.09246013e-8%0A%5Cend%7Balign%2A%7D%0A)

### **Probability of win for multible tickets**
We are not done yet. Since, we want to know how many draws do we need to reach a target probability for at least 1 win, we need to extent the above for multiple tickets. To do that the easiest way is to calculated what is the probability of losing every time and subtracting it from 100%. To do that we find the probability of losing with 1 ticket which is:

![\begin{align*}
\color{red} \large
P_{lose} = 1 - P_{win}
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0AP_%7Blose%7D+%3D+1+-+P_%7Bwin%7D%0A%5Cend%7Balign%2A%7D%0A)

If we want to know the probability of losing 2 times in a row, all we need to know is multiple the probability of the two events since they are independed from each other. In general, the probability of losing ***n*** times is given:

![\begin{align*}
\color{red} \large
P_{lose,n} = P_{lose}^n
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D+%5Clarge%0AP_%7Blose%2Cn%7D+%3D+P_%7Blose%7D%5En%0A%5Cend%7Balign%2A%7D%0A)

### **Solution**
Since we know the target probability of winning, all we need to do is solve the above equation for ***n*** with the probability of losing ***n*** times equal to 1 minus the *target* probability. For example, for a target probability of 90% the avobe becomes:

![\begin{align*}
\color{red}
P_{lose,n} = 1 - 0.9=0.1 =P_{lose}^{n} 
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D%0AP_%7Blose%2Cn%7D+%3D+1+-+0.9%3D0.1+%3DP_%7Blose%7D%5E%7Bn%7D+%0A%5Cend%7Balign%2A%7D%0A)

The smart way to solve the above equation is to do so analytically using logarithms as follows:

![\begin{align*}
\color{red}
n = \log_{P_{lose}} P_{lose,n}
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D%0An+%3D+%5Clog_%7BP_%7Blose%7D%7D+P_%7Blose%2Cn%7D%0A%5Cend%7Balign%2A%7D%0A)

From there one needs to find a way to calculate the above logarithm. A Taylor series is a great way to do that. I will probably implement that at the future.

However, since we are lazy and not smart there is always the easy route. All we need to do is try numbers starting from 1 until the probability of losing once raise to the power of that number is smaller than the target probability.

There are two problem with this approach though:
1. If the number ***n*** is too big (which is in our problem), let say 1000, no calculator can perform the operation *x<sup>1000</sup>*. Although, the C++ `pow` function can so no real problems there.
2. It is a slow algorithm. The number of draws for just a 50-50 chance is in the order of tens of millions. This means that we need millions of iteration to compute just 50% chance.

To speed up the process we start the iterations with just the probability of losing once and on each iteration we multiple the number of the previous iteration by the initial probability to the power of 1000:

![\begin{align*}
\color{red}
{({({(P_{lose})}^10)}^10)}^10
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D%0A%7B%28%7B%28%7B%28P_%7Blose%7D%29%7D%5E10%29%7D%5E10%29%7D%5E10%0A%5Cend%7Balign%2A%7D%0A)

The reason why we do it like that is to speed up the execution of the power function. Although, as the `pow` function is very optimized the difference might not exist. Once we get close enought to the value we change to power to 100 and then 10 and finally 1 until we reach the target.

Of course this is just an approximation and as such the solution is probably off by a few draws. However, since the number of draws are to the order of tens of millions the error for 1000 draws off is <0.01%. I my experience this is good enough. 

After a bit of testing, according to python `math.log`, the algorith is off by 1-2 draws or <0.00001%. 

## **Expected value per ticket**
A much more interesting result is the expected value of the ticket. This figure can tell us the value that we get with each ticket that we buy. For instance, if the expected value is 1 euro, then for each ticket that we buy we make 1 euro.

However, we should nod that even if the value is positive that doesn't necessarily that we will make money playing. The real meaning is that we will eventually, if we keep playing, go positive, but this could be after 10 tickets or 1 million tickets. The more positive, the less time it will probably take, if the cost is fixed. Still though, it is a figure worth calculaing.

### **Mathimatical definition**
By definition, the expected value is the sum of all the possible outcomes multiplied by their probabilities or in mathimatical terms:

![\begin{align*}
\color{red}
EV = \sum{P(X_i)\times X_i}
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D%0AEV+%3D+%5Csum%7BP%28X_i%29%5Ctimes+X_i%7D%0A%5Cend%7Balign%2A%7D%0A)

Where *X<sub>i</sub>* is the outcome *i* and *P(X<sub>i</sub>)* the probability of the outcome *i*.

### **The nature of the problem**
At a first glance, it seems like it is a simple problem. Since there are 8 price teir, all we need to do is multiply each of the prices with their corresponding probability. This is a good option if we want some results fast. However, this approach is wrong as by so we are assume that there can only be one winner in each tier. In reality, if multiple winners win in the 5+1 tier (or the Jackpot) the price is split. The difference between the correct and fast approach is small if the number of the total tickets is small, but as more people are playing the difference in the two results grows rapidly.

The three factores that influances the expected value of the ticket are:
1. The cost of the ticket.
2. The prices of each tier (mainly the Jackpot).
3. The number of tickets in each draw.

From the above, only the last two vary as the cost of the tickets is fixed. This is if you neglect the cases where you can buy a ticket with more that 5+1 guesses. To take that into account we would need to know the exact formula that is used to calculate the extra cost of the ticket, which is info that we don't have. So for simplicity we will ignore that. In any case, the formula that is being used is probably designed to decrease the expected value even further, as they try to maximize their profits.

So, what we need to do is evaluate the probability of us winning while there are *n* winners and multiply that with the price divided by the number of winners (for each tier). To do that we first need to find what is the probability of *n* people share the same winning guess. This is a very similar problem with a well studied statistics problem known as *"The birthday paradox"*. We will note explain the problem here, but the details of the problem can be found at the references.

## Solution
Directly applying the analytical solution here is unfeasible due to the large number being involved. For the analytical solution we need to calulate the compinations of large number, which involves huge factorials. This is impossible as we will not only have problems with overflow and/or rounding errors but computational time as well. 

For the reasons above an approximation must be made. Thankfully there we have an available option. By using the Taylor series of the exponential function, *e<sup>x</sup>*, the solution can be approximated by Poisson's formula:

![\begin{align*}
\color{red}
P(n)=\dfrac{\lambda^n\e^{-\lambda}}{n!}
\end{align*}
](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Balign%2A%7D%0A%5Ccolor%7Bred%7D%0AP%28n%29%3D%5Cdfrac%7B%5Clambda%5En%5Ce%5E%7B-%5Clambda%7D%7D%7Bn%21%7D%0A%5Cend%7Balign%2A%7D%0A)

To be continued... (passive-aggressive)

# Results
to be filled... (passive-aggressive)

# **References**
- Joker Guide: https://www.opap.gr/en/how-to-play-joker
- Joker Cost Calculator: https://www.opap.gr/en/joker-cost-calculator
- Birthday Paradox: https://en.wikipedia.org/wiki/Birthday_problem
- Poisson Distribution: https://en.wikipedia.org/wiki/Poisson_distribution