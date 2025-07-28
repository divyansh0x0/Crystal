OpenGL Nomenclature Explained Super Simply (Python Style)

OpenGL function names can look like a secret code, but they’re just telling you what the function does, what data it uses, and what it affects. Think of it like naming Python functions with extra info. Let’s break it down in super simple terms, like explaining it to someone who knows basic Python.

* * *

1\. Function Suffixes: Numbers and Letters

Some OpenGL functions are like Python functions that do the same thing but take different types of data (like int or float) or different numbers of inputs. Instead of making separate names, OpenGL adds suffixes (extra bits) to the function name to show these differences.

The pattern is like this:

FunctionName\[Number\]\[Type\]\[v\]

*   Number (1–4, optional): How many inputs the function takes.
    
    *   Example: glVertexAttrib3f means it takes 3 values, like my\_func(x, y, z).
        
    *   If there’s no number, the number of inputs depends on something else.
        
*   Type: What kind of data the function takes (like Python’s int, float, etc.). Here’s what the letters mean:
    
    Letter
    
    Python-like Type
    
    b
    
    Small integer (like
    
    int
    
    , but tiny)
    
    s
    
    Small integer (a bit bigger)
    
    i
    
    Regular integer (like
    
    int
    
    )
    
    i64
    
    Big integer (64-bit)
    
    ub
    
    Positive small integer
    
    us
    
    Positive medium integer
    
    ui
    
    Positive regular integer
    
    ui64
    
    Positive big integer
    
    f
    
    Float (like
    
    float
    
    )
    
    d
    
    Double (like a super precise
    
    float
    
    )
    
    Example: glVertexAttrib3f takes 3 floats, like my\_func(1.0, 2.0, 3.0).
    
*   v (optional): Means the function takes a list (like a Python list) instead of separate values.
    
    *   Example: glVertexAttrib3fv takes a list of 3 floats, like my\_func(\[1.0, 2.0, 3.0\]).
        
    *   If there’s a number (like 3), the list must have exactly that many items.
        
    *   If no number, the list size depends on another input.
        
    
    Output case: Sometimes v means the function fills a list with results, like:
    
    python
    
        results = [0, 0, 0]
        glGetSomethingv(results)  # Fills results with values
    

Python-like example:

python

    # Like glVertexAttrib3f
    def set_vertex_attrib_3f(x: float, y: float, z: float):
        print(f"Setting 3 floats: {x}, {y}, {z}")
    
    # Like glVertexAttrib3fv
    def set_vertex_attrib_3fv(values: list[float]):
        print(f"Setting 3 floats from list: {values}")

* * *

2\. Weird Suffixes: Special Cases

Some functions, especially ones that “get” info from OpenGL (like checking settings), don’t follow the usual pattern:

*   Spelled-out types: Some functions use full words like Boolean or Integer instead of b or i.
    
    *   Example: glGetIntegerv is like a Python function that returns a list of integers:
        
        python
        
            def get_integers() -> list[int]:
                return [1, 2, 3]
        
*   i\_v for indexed stuff: Functions like glGetFloati\_v get info using an “index” (like a list index) and return a list.
    
    *   i: Means it uses an index (not that it returns integers).
        
    *   v: Means it returns a list.
        
    *   Example: Like a Python function that gets floats from a specific “slot”:
        
        python
        
            def get_floats_at_index(index: int) -> list[float]:
                return [1.0, 2.0]  # Depends on index
        
*   Not a suffix!: Some letters look like suffixes but are part of the function’s name.
    
    *   Example: glVertexAttribI4i. The I isn’t a type; it’s part of the name (glVertexAttribI), meaning it handles data differently. The 4i means “4 integers.”
        

* * *

3\. Function Names: Action, Thing, Details

OpenGL functions often work with objects (like textures or buffers), which are like Python objects that store data. Function names are built like this:

Action-Thing-Details

*   Action: What the function does (like a Python method).
    
    *   Examples: Get (read data), Draw (show stuff), Enable/Disable (turn on/off).
        
    *   Example: Get in glGetIntegerv is like obj.get\_data().
        
*   Thing: What the function affects (like a Python class).
    
    *   Examples: Texture, Framebuffer, Buffer.
        
    *   Example: glFramebufferTexture affects a framebuffer.
        
*   Details: Extra info about what’s happening.
    
    *   Example: glFramebufferTexture attaches a texture to a framebuffer.
        

Sometimes parts are missing:

*   No Action: Means it sets something (like obj.set\_value()).
    
    *   Example: glSamplerParameterf sets a sampler’s settings.
        
*   No Thing: Means it affects global settings, not a specific object.
    
    *   Example: glDrawBuffers affects framebuffers but doesn’t say “Framebuffer.”
        
*   No Details: Often for creating or checking objects.
    
    *   Example: glGenTextures is like Texture.create().
        

Not always clear:

*   Some functions affect objects but don’t name them (e.g., glDrawBuffers works on framebuffers).
    
*   If a function names a thing (e.g., glFramebufferTexture), it definitely affects that thing.
    

Python-like example:

python

    class Framebuffer:
        def attach_texture(self, texture):
            print(f"Attaching {texture} to framebuffer")
    
    # Like glFramebufferTexture
    framebuffer = Framebuffer()
    framebuffer.attach_texture("my_texture")

* * *

4\. Object Names: What Things Are Called

OpenGL uses specific names for objects in function names, like class names in Python:

Object

Name in Functions

Texture

Tex

Framebuffer

Framebuffer

Buffer

Buffer

Sampler

Sampler

Query

Query

Transform Feedback

TransformFeedback

Other objects (like shaders) don’t have consistent names, which can be annoying.

* * *

5\. Direct State Access (DSA): Skip the Setup

Normally, to change an object, you “select” it first (like setting obj.active = True) and then modify it. Direct State Access (DSA), added later, lets you change objects directly by using their ID, like passing an object to a function. DSA names are clearer but use different object names.

DSA Object Names:

Object

Old Name

DSA Name

Texture

Tex

Texture

Framebuffer

Framebuffer

NamedFramebuffer

Buffer

Buffer

NamedBuffer

Transform Feedback

TransformFeedback

TransformFeedback

Vertex Array

None

VertexArray

Sampler

None

Sampler

Query

None

Query

Program

None

Program

Python-like example:

python

    # Old way (non-DSA)
    buffer = Buffer()
    buffer.bind()  # Select it
    buffer.set_data([1, 2, 3])  # Change it
    
    # DSA way
    buffer = Buffer()
    buffer.set_data_direct([1, 2, 3])  # No binding, just use ID

Small quirk:

*   Some DSA names add Named (e.g., NamedBuffer), others just use a longer name (e.g., Texture instead of Tex).
    
*   A few old functions (e.g., glClearTexImage) act like DSA but use non-DSA names.
    

* * *

Why It’s Confusing

OpenGL has been around forever (since the 1990s), so it’s like a big Python project with old and new code mixed together. New features were added, but old functions stayed to avoid breaking things, so names aren’t always consistent.

* * *

Quick Tips to Get It

1.  See numbers and letters at the end? They tell you how many inputs and what type (e.g., 3f = 3 floats).
    
2.  See a v? It’s a list, not separate inputs.
    
3.  Look at the name: Action-Thing-Details shows what it does and what it affects.
    
4.  DSA functions? They’re simpler and use names like NamedBuffer.
    
5.  Weird i\_v stuff? It’s getting data from a specific “slot.”
    

* * *

Think of OpenGL names like Python function names with extra hints. For example, glNamedFramebufferTexture is like framebuffer.attach\_texture\_direct(). It gets easier with practice! Want me to explain a specific function or idea in Python terms? Just let me know!