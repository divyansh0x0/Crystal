namespace crystal::graphics
{
    enum class GraphicsAPI
    {
        OpenGL = 0,
        DirectX = 1
    };
    class Context{
        public:
        void begin();
        void end();
    };
    class GraphicsContext:public Context{
        public:
            void setVertexBuffer();
            void setIndexBuffer();
    };
}
