# Stack

Stack is an [esolang](https://esolangs.org/wiki/Esoteric_programming_language)
that uses four operators (`^`, `>`, `=`, `<`) to manipulate the tape memory
cells, or the pointer on that tape.

The only inputs accepted by Stack are the four operators as described below,
digits, and the `-` symbol to denote a negative digit. 

| Operator | Description                              | Example |
|----------|------------------------------------------|---------|
| `^`      | Grow the tape by the given amount        | `1024^` |
| `>`      | Jump up the tape by the given amount     | `10>`   |
| `=`      | Set the current cell to the given amount | `72=`   |
| `<`      | Get the value in the current cell        | `<`     |

Operators that accept arguments are expected to have the argument preceding the
operator, for example to grow the tape by a given amount you would put `1024^`.

## Hello World

Below is an example Hello World program formatted for readability.

    12^
    72=1>101=1>108=1>108=1>111=1>
    32=1>
    87=1>111=1>114=1>108=1>100=1>10=1>
    -12>
    <1><1><1><1><1>
    <1>
    <1><1><1><1><1><1>

The first line sets the size of the tape to 12. There is no limit to the
number of times the `^` operator can be invoked. Each invocation will add to
the current size of the tape.

    12^

On the second, third, and fourth lines the string `Hello World` is set in the
tape, jumping forward one after each value that is set.

    72=1>101=1>108=1>108=1>111=1>
    32=1>
    87=1>111=1>114=1>108=1>100=1>10=1>

The above code can be put all on one line, or each operator can be put on a new
line.

On the fifth line we jump back to the start of the tape. This is done by giving
a negative value to the `>` operator.

    -12>

>**Note:** Negative values are valid for all operators meaning it is possible to
shrink the stack. However this implementation of Stack will prevent you from
having a negative tape size.

The final three lines of the program then print out the string `Hello World` we
stored on the tape. This is done by using the `<` operator, the only operator
that does not take an argument. After each invocation of `<` we jump forward
once.

    <1><1><1><1><1>
    <1>
    <1><1><1><1><1><1>
