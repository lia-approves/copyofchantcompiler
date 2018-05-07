# Parser Combinator

## Basic Concept

Our library is composed of _parser creators_: functions which create parser functions.  For example, `Literal('a')` creates a parser which matches the literal character 'h' (so `Literal` is _not_ the actual parser).

Because a parser creator can take a parser as a parameter (yay higher-order functions!), our library functions can be composed endlessly.  With a library function for each PEG operator, you could write your grammar directly in code.

## Performance

As far as I understand it, there are two required performance enhancements we'll need to implement: memoization and lazy evaluation.

*Memoization* is easy.  Since our library functions depend only on their parameter (a State object), we can simply map States to parse results.  It's not quite as space-efficient as the tabular approach most papers seem to use, but it works.

*Lazy evaluation*, if you don't know, is where a value is computed only when it is needed.  This provides the largest performance improvement of all, since it allows us to avoid unecessary parsing (some parse results are never needed; with lazy evaluation, they would never even be computed).  In Haskell, the poster child for Parser Combinators, lazy evaluation is built into the language.  However, I have no idea how to emulate this is C++.

In fact, I'm not even sure if we _need_ to do so at all.  The paper I read built their memoization table from the bottom up, meaning that their approach does a lot of unecessary work.  Since our approach is top-down, isn't that kinda the same amount of work as the lazy-evaluated approach?

## Converting to an AST

This is one of the things I'm unsure about.  Since we're making a library that should be able to represent any language, it probably shouldn't be dependent on the ASTs we're provided, right?  Since a user's language might have constructs that differ from the AST we use.

So, we need a way to allow the library user to specify how the parsed expressions convert to AST nodes.

There is one good approach I can think of.

### Accumulate the AST in the Result objects, using an extra Convert function parameter

Include an AstNode field in the Result class (but make it a template so users supply their own AstNode class).  Make all parse function generators take an extra parameter: a function that converts the parse results into an AST node.  This approach is flexible and easy to reason about.  However, it gets awkward with parsers that don't generate AST nodes (for example, ones that consume excess whitespace).

## Questions

* How should we convert the expressions to an AST?
* Assuming we add simple memoization, is our code efficient enough to meet the requirements of this class?  Is this even a packrat parser?
* How should we handle types?  The example I based this code on has dynamic typing, which allowed various data types to coexist within a parse function.  I don't think that's possible for us.  For example, an Or parser generatos 3 types to worry about: the first parser result, the second, and the overall result of the Or.  That overall result could be of type A or B, but _we don't know which_ until runtime.  The C library I looked at just makes all results Strings, and lets the AST converter worry about casting those strings to their appropriate value.  Is that okay?

Basically, we need a code review from someone who knows what they're doing.

