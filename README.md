# IncludeAny

Allows including any object, not just modules. Of course, this is just in
theory—see “Bugs & Caveats” below.

## Installation

Simply run

    $ gem install include_any

or include it in your Gemfile as usual.

## Usage

The method of interest here is `IncludeAny.include_any`. By default this is not
mixed-in anywhere, but doing

    require 'include_any/core_ext'

will `include IncludeAny` into `Class` and `Module`.

Then we can get going:

    class C
      def foo
        'bar!'
      end
    end

    class D
      include_any C
    end

    D.ancestors.include? C
    #=> true

    D.new.foo
    #=> "bar!"

Well would you look at that! We’ve included a `Class`. Magical!

## Bugs & Caveats

Use at your own risk, kids.

- Currently seg faults if passed anything but a `Class` or `Module`. It should
  accept (most) any object.
- Will probably fail to install or seg fault under anything but MRI 1.9.3

See the issues for more.

## Contributing

Patches and improvements welcome. Especially if they fix a seg fault. Note that
there is no intention to support Ruby 1.8.

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

## Credits

© 2012 J. Andrew Marshall. All rights reserved. See the LICENSE file for more
information.
