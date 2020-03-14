<h1> UNO - The small, but powerful, mathematically precise shell </h1>
<p>
UNO is the byproduct of a bored CS and Math student on break. The goal of UNO is
to create a sandbox as mathematically precise as possible in an intuitive manner.
There is one type in uno, Rational Number (rat), which allows for well defined operations.
UNO uses the c++ boost library to provide up to 1024 bit integer precision, as
well as 100 digit float precision. UNO also has some additional features that
make it useful and intuitive.
</p>
<br>

<h1> Basic Operations </h1>
<p>
UNO comes provided with all the basic arithmetic operations: addition, subtraction,
multiplication, division, and exponentiation.<br>

<code> 5 + 5 # 10 </code><br>
<code> 15 - 5 # 10 </code><br>
<code> 5 * 2 # 10 </code><br>
<code> 50 / 5 # 10 </code><br>

</p>
<h2> Exponentiation </h2>

<p>
UNO, along with the normal <code>^</code> exponent operator, comes with shorthands for powers
and root, as shown below (<code>**</code> and <code>//</code>).<br>

<code> uno > 5 ^ 2 # 25 </code><br>
<code> uno > 5 ** 2 # 5 ^ 2 = 25 </code><br>
<code> uno > 25 // 2 # 25 ^ (1/2) = 5 </code><br>

</p>
<h2> Expressions </h2>
<p>
These operations can be combined in an intuitive manner to create arbitrary expressions.<br>

<code> uno > 5 + 5 - 2 # 8 </code><br>
<code> uno > 2 ** 2 // 2 # 2 </code><br>
<code> uno > 2 ^ (6.5 - (1.5 * 3)) # 4 </code><br>
</p>

<h1> Number Representations </h1>
<p>
In UNO, numbers can be represented as either fractions, or decimals. The
<code>dec</code> and <code>frac</code> commands display numbers in a specified manner.

<code> uno > dec 4/5 # 0.8 </code><br>
<code> uno > frac .8 # 4/5 </code><br>

You can also used the ~ operator to represent repeating decimals, as shown below.
In UNO, this is implemented via geometric series calculations. <br>

<code> uno > dec 1/3 # 0.~3 </code><br>
<code> uno > frac .~9 # 1, note that .9 repeating is mathematically defined as 1 via the geometric series</code><br>
<p>
<h2> Variables </h2>
<p>
In UNO, variables are relatively easy to use.<br>

<code> uno > x = 2//2 # define x as sqrt(2)</code><br>
<code> uno > y = x ** 4 # y = 4 </code><br>
</p>

<h1> Lambda Expressions/Formulas </h1>
<p>
In UNO, lambda expressions can be created quickly and intuitively. A lambda expression
is denoted by the <code>:=</code> identifier. The first token is the lambda name,
the rest are parameter names, and the right of the <code>:=</code> token is the
body.

<code> pythag_theorem a b := (a**2 + b**2)//2</code><br>
In this example, the lambda name is pythag_theorem, and the parameters are a and b.
The lambda can then be evaluated using arbitrary values.<br>

<code> pythag_theorem 3 4 # 5</code><br>
Lambda bodies can also be used in place in expressions, as represented by the
example code below.

<code> uno > sqrt a := a//2</code><br>
<code> uno > x = 25</code><br>
<code> uno > y = (sqrt x) ** 3 # set variable y to be 125</code><br>
</p>

<h1> Functions </h1>
<i>To be added soon </i>

<h1> Miscellaneous </h1>

<h2> UNO defined constants </h2>

UNO brings along some predefined constants, such as <code>pi</code> and <code>e</code>
These constants cannot be redefined.<br>


<code> uno > c_area r := pi * (r**2)</code><br>
<code> uno > c_area 5 # 78.53...</code><br>
<code> uno > pi = 5 # error, uno defined constants cannot be redefined </code><br>

<h2> Helpful Commands </h2>
UNO comes with some helpful commands.<br>

<code>show</code> Shows list of current variables and lambda expressions.<br>
<code>clear</code> Clears all current variables and lambda expressions.<br>
<code>history</code> Displays UNO command history<br>
<code>dec [rat]</code> Displays number token as a decimal.<br>
<code>frac [rat]</code> Displays number token as a fraction.<br>

<h1> Download and Requirements </h1>
UNO can be downloaded with a simple<br><code>git clone https://github.com/lfzbrennan/uno.git</code><br>
Followed by a<br><code>make</code> to create the uno executable. <br>

In order to compile, the boost c++ library must be downloaded, and $BOOST_PATH
must be set. At this time, UNO can only be downloaded on *NIX systems.
