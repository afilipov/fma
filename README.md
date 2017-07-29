A moving average is commonly used with time series data to smooth out
short-term fluctuations and highlight longer-term trends or cycles. The
threshold between short-term and long-term depends on the application, and the
parameters of the moving average will be set accordingly. For example, it is
often used in technical analysis of financial data, like stock prices,
returns or trading volumes. Mathematically, a moving average is a type of
convolution, and so it can be viewed as an example of a low-pass filter
used in signal processing. When used with non-time series data, a moving
average filters higher frequency components without any specific connection
to time, although typically some kind of ordering is implied. Viewed
simplistically it can be regarded as smoothing the data.

Example:

make

./bin/fma_demo >data.txt

gnuplot

gnuplot> plot "data.txt" using 1:2 title 'Input' with lines, "data.txt" using 1:3 title 'Average' with lines
