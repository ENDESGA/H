<p align="center">
  <img src="https://github.com/user-attachments/assets/6b22f545-74ac-46b5-b72f-cb01910d9d65" alt="hydrogen">
</p>

# ***H*** *-------< h language >*
***an explicit, minimal, and readable abstraction.***

reimagining C in a vacuum, using short and clear words from the average lexicon. designed to flow.
the goal is to maximize legibility and literal understanding upon initial code reading; the best hydrogen code is read and understood without the need for comments.

just bytes, types, references, and functions:
```c#
fn do_thing( in s4 ref a, in s4 b ) { val_of( a ) += b; }
```
-------
## systematic rules and restrictions
- everything is just bytes and references.
- newly allocated bytes are zeroed.
- all `ref` types are constant and restricted.
- structs are packed, with descending-size components.
- text characters are unsigned bytes.
- function parameters are constant via `in`.
- all memory is contained and tracked.
-------
## type prefixes
- temporary/permanent variable: `temp` or `perm`
- constant variable: `const`
- structure of object: `struct`

## type groups
- **value** types:
  - arbitrary byte: `byte`
  - unsigned bytes: `u1`, `u2`, `u4`, `u8`
  - signed bytes: `s1`, `s2`, `s4`, `s8`
  - floating-point bytes: `f4`, `f8`
- **struct** types:
  - pixel canvas: `canvas`
  - pixel: `rgba2`, `rgb3`, `rgba4`
- **object** types:
  - dynamic array: `list`
  - dynamic bytes: `text`
 
## type suffixes
- constant reference: `ref`
- mutable reference: `mutable_ref`

-------
-------
-------
-------
-------
-------
-------
