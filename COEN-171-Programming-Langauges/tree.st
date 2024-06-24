Object subclass: #Node
instanceVariablNames: 'data left right'
classVariableNames: ''
poolDictionaires: ''

!Node methodFor: 'homework'!
initialize: anObject
	data:= anObject
!

member: x 
	x < data ifTrue: [
		left isNil ifTrue: [
			^false
		] ifFalse: [
			^left member: x
		]
	] .
	x > data ifTrue[
		right isNil ifTrue [
			^ false
		] ifFalse: [
			^right member: x
		]
	] .
	^ true
!!

Objecct subclass: #Tree
instanceVariablNames: 'root'
classVariableNames: ''
poolDictionaires: ''

!Tree methodsFor: 'homework'!
member: anObject
	root isnil ifTrue: [!false] ifFalse: [^root member: anObject]
!

insert: x
	root isnil ifTrue: [
		root := Node new
		initialize: x
	] ifFalse: [
		'TODO'
	]
!!
