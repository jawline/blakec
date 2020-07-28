## C data structure collection

This project contains implementations of common C data-structures declared
through code-generating macros. The motivation for developing this project
came from the observation that when choosing a C data-structure implementation
you often need to sacrifice type-safety, since macros or pointers are used
to be generic. Additionally, I noticed that implementation specific details,
such as embedding keys into data or methods not including safety-checks
often lead to nasty errors at runtime.

By using macros to declare new functions we are able to build a generic
implementation of these data structures while enabling type-checking. Another
advantage is that we enable storage of elements that do not live on the heap,
since data can be stored directly rather than by reference, which reduces
memory management burden in some instances.

The implementations are designed to be simple to use, with a focus on a
simple API and rules for usage that don't require an in-depth knowledge of the
underlying implementation. The implementations are designed to be fast enough
for most applications, but are not meant to be the fastest around. In most
$cases they are tuned for runtime safety, rather than insert or lookup speed.

Implementation is in headers, so you do not need to link anything to use
these tools.


### Getting Started (User)

To use in an existing program, add `-I PATH_TO_BLAKEC/src/` to linking
options and include the desired implementation. For usage examples, see the
test cases we show declaration of new structures and how to use them. The
implementation header files also contain in-line documentation through
comments on each supplied method.

### Getting Started (Developer)

We use Ceedling to manage development builds and unit testing,
which includes Valgrind integration so that our test-cases are
tested for memory leaks. A nice write-up of Ceedling is available
[here](http://www.throwtheswitch.org/ceedling) with instructions on getting
setup in various different environments.

To run the unit tests after making a change execute:
```shell
ceedling test
```

### Dependencies

For developing we use Ceedling, but that is only necessary if you want to
execute the test cases. In other cases all you need is a C compiler.
