# MVC Tetris

This is an attempt at making tetris using the MVC coding pattern,
using threepp for rendering using the OpenGL rendering API.

By using the MVC coding pattern the rendering engine can easily be
changed, as the rendering code is located only mostly in the view.

It has most of the functionality of the modern version of tetris,
and has a hold function, a preview of the next piece and a display
of the score.

The controls are the same as most modern implementations of tetris.

```
SPACE->instant drop
DOWN->soft drop
LEFT->move left
RIGHT->move right
Z->rotate counter clockwise
UP->rotate clockwise
C->hold
R->restart
P->pause
```

---

As `vcpkg` is used, you need to tell CMake about it in order for dependency resolution to work: 

`-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`

###### Building under MinGW

Under MinGW you'll need to specify the vcpkg triplet:
```shell
-DVCPKG_TARGET_TRIPLET=x64-mingw-[static|dynamic]  # choose either `static` or `dynamic`.
-DVCPKG_HOST_TRIPLET=x64-mingw-[static|dynamic]    # <-- needed only if MSVC cannot be found. 
```
