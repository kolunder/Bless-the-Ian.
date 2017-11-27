Description: 
	The list is implemented via using a single sentinel node, which cycles to link to itself upon construction. The list is a cycle but cannot be traversed after the end or before the beggining due to checkX() functions. 

	The functions linking back to the start (atStart() and atEnd()) are admittedly quite ineficient as both utilise go(), which goes forward until reaching sentinel node.

Problems:
	The chat around the cohort made me stressfully question my implementation, hastly changing it before eventually returning to the initial code, whlist preserving the list.h integrity. Please comment on the robustness of my implementation, as I struggle to become confident in most programs I write. It always seems as though there is better ways out there.


Thank you for your time!