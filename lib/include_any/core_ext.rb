require 'include_any'

class Class
  include IncludeAny
  private :include_any
end

class Module
  include IncludeAny
  private :include_any
end
