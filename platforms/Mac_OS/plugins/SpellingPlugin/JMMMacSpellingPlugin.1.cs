'From Squeak3.8 of ''5 May 2005'' [latest update: #6665] on 15 June 2005 at 5:04:15 pm'!
		interpreterProxy pushRemappableOop: arrayOop.
		value := interpreterProxy positive32BitIntegerFor: (result at: i).
		arrayOop := interpreterProxy popRemappableOop.
		interpreterProxy storePointer: i ofObject: arrayOop withValue: value].
! !