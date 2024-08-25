<p align="center">
  <img src="https://github.com/user-attachments/assets/6b22f545-74ac-46b5-b72f-cb01910d9d65" alt="hydrogen">
</p>

# ***H*** *- < hydrogen language >*
***an explicit, minimal, and readable abstraction.***

reimagining C in a vacuum, using short and clear words from the average lexicon. designed to flow.
the goal is to maximize legibility and literal understanding upon initial code reading; the best hydrogen code is read and understood without the need for comments.

just bytes, types, references, and functions:
```c#
fn do_thing( in s4 ref a, in s4 b )
{
  val_of( a ) += b;
}
```
-------
## systemic restrictions
- everything is just bytes and references.
- newly allocated bytes are zeroed.
- all `ref` types are constant and restricted.
- structs are packed, with descending-size components.
- text characters are unsigned bytes.
- function parameters are constant via `in`.
- all memory is contained and tracked.
- everything is in ***snake_case***
- names follow a strict form: `external verbs` `noun` `internal verbs`
  - `new_list( type )` "make a new list of type" (verb to noun)
  - `delete_list( list )` "delete this list" (verb to noun)
  - `copy_list( from_list, to_list, at_pos )` "copy from this list, to this other list's position" (verb to noun)
  - parameters and internal verbs are in "action-order"
    - *you can't insert a value until you've made room at the position*
  - `list_insert( list, pos, val )` "with this list, insert at this position: this value (type is inferred from value)" (noun's verb)
  - `list_get( list, type, pos )` "with this list, of this type, get from this position" (noun's verb)
  - `list_add_list( this_list, other_list )` "with this list, add this other list" (noun's verb)
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

## example code
*unit test for list insertion:*
```c
// since it has no output, it's just `fn`
fn UNIT_TEST_LIST_INSERT()
{
	temp list test_list = new_list( s4 );
	iter( i, 5 )
	{
		list_add( test_list, i );
	}
	list_insert( test_list, 2, 7 );
	//
	expect( test_list->size > 5 );
	expect_val( s4, list_get( test_list, s4, 2 ), 7 );
	expect_val( s4, list_get( test_list, s4, 3 ), 2 );
	//
	delete_list( test_list );
}
```
*list_insert_list implementation:*
```c
// `embed` before the output type embeds the function where it's used
embed list list_insert_list( in list this_list, in u4 in_pos, in list other_list )
{
	temp const u4 old_size = this_list->size;
	temp const u4 pos = CLAMP( in_pos, 0, old_size );
	resize_list( this_list, this_list->size + in_other->size );
	list_move( this_list, pos, old_size - pos, to_s4( in_other->size ) );
	copy_list( in_other, this_list, pos );
	//
	out this_list;
}
```

-------
-------
-------
-------
-------
-------
-------
