<h1> UNO - The small, but powerful, mathematically precise shell <h1>
UNO is the byproduct of a bored CS and Math student on break. The goal of UNO is
to create a sandbox as mathematically precise as possible in an intuitive manner.
There is one type in uno, Rational Number, which allows for well defined operations.
UNO uses the c++ boost library to provide up to 1024 bit integer precision, as
well as 100 digit float precision. UNO also has some additional features that
make it useful and intuitive.

<br>

<h1> Basic Operations </h1>
UNO comes provided with all the basic arithmetic operations: addition, subtraction,
multiplication, division, and exponentiation.<br>

<code> 5 + 5 # 10 </code><br>
<code> 15 - 5 # 10 </code><br>
<code> 5 * 2 # 10 </code><br>
<code> 50 / 5 # 10 </code><br>

<h2> Exponentiation <h2>
UNO, along with the normal ^ exponent operator, comes with shorthands for powers
and root, as shown below.<br>

<code> 5 ^ 2 # 25 </code><br>
<code> 5 ** 2 # 5 ^ 2 = 25 </code><br>
<code> 25 // 2 # 25 ^ (1/2) = 5 </code><br>

<h2> Expressions <h2>
These operations can be combined in an intuitive manner to create arbitrary expressions.<br>

<code> 5 + 5 - 2 # 8 </code><br>
<code> 2 ** 2 // 2 # 2 </code><br>
<code> 2 ^ (6.5 - (1.5 * 3)) # 4 </code><br>

<h1> Number Representations <h1>
In UNO, numbers can be represented as either fractions, or decimals. The
<code>dec</code> and <code>frac</code> commands display numbers in a specified manner.

<code> dec 4/5 # 0.8 </code><br>
<code> frac .8 # 4/5 </code><br>

You can also used the ~ operator to represent repeating decimals, as shown below.
In UNO, this is implemented via geometric series calculations. <br>

<code> dec 1/3 # 0.~3 </code><br>
<code> frac .~9 # 1, note that .9 repeating is mathematically defined as 1 via the geometric series</code><br>

<h2> Variables </h2>
In UNO, variables are relatively easy to use.<br>

<code> x = 2//2 # define x as sqrt(2)
y = x ** 4 # y = 4
</code><br>
