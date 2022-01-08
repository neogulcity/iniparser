namespace ini
{
    class ini
    {
        std::string path;
    public:
        ini(std::string _path) : path(_path) {}
        std::string get(std::string _section, std::string _arg, std::string _default);
    };   
}