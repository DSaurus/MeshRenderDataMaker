# OBJ file format

# vertex command

` v x y z `

This is the vertex command. In this simplified version of the specification, we will only cover polygonal faces, therefore the vertex command can be used to specify the vertices of the polygon. When using freeform surfaces and curves, there is a similar command vp that can be used to specify control points of the surface or curve.

The v command specifies a vertex by its three cartesian coordinates x, y, and z. The vertex is automatically assigned a name depending on the order in which it is found in the file. The first vertex in the file gets the name  ‘1’, the second as ‘2’, the third as ‘3’ and so on.

# vertex normal command

` vn x y z `

This is the vertex normal command. It specifies the normal vector to the surface. x, y and z are the components of the normal vector. Note that this normal vector is not yet associated to any vertex point. We will have to associate it with a vertex later with another command called the f command.

The vertex normal command is omitted in a lot of files because when we will group vertices into polygonal faces with the f command, it will automatically determine the normal vector from the vertex coordinates and the order in which the vertices appear.

# vertex texture command

` vt u v [w] `

The vertex texture command specifies a point in the texture map, which we covered in an earlier section. U and V are the X and Y coordinates in the texture map. These will be floating point numbers between 0 and 1. They really don’t tell you anything by themselves, they must be grouped with a vertex in a f face command, just like the vertex normals.

# face command 

`f v1[/vt1][/vn1] v2[/vt2][/vn2] v3[/vt3][/vn3] ...`

The face command is probably the most important command. It specifies a polygonal face made from the vertices that came before this line.

To reference a vertex you just follow the implicit numbering system of the vertices. For example ‘f 23 24 25 27’ means a polygonal face built from vertices 23, 24, 25 and 27 in order.

For each vertex, you may associate a vn command, which then associates that vertex normal to the corresponding vertex. Similarly, you can associate a vt command with a vertex, which will determine the texture mapping to use at this point.

If you specify a vt or vn for a vertex, you must specify it for all of them.