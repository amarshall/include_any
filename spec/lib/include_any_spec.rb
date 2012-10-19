require 'spec_helper'

describe 'IncludeAny#include_any' do
  it "should work when including a class" do
    d = Class.new
    c = Class.new do
      extend IncludeAny
      include_any d
    end

    c.ancestors.should include d
  end

  it "should work when including a module" do
    m = Module.new
    c = Class.new do
      extend IncludeAny
      include_any m
    end

    c.ancestors.should include m
  end

  it "should work when including the object being defined" do
    pending 'it seg faults'

    c = Class.new do
      extend IncludeAny
      include_any c
    end

    c.ancestors.should include c
  end

  it "should work when including a non-Class/Module object" do
    pending 'it seg faults'

    o = Object.new
    Class.new do
      extend IncludeAny
      include_any o
    end

    c.ancestors.should include o
  end

  it "should work with super" do
    d = Class.new do
      def f; 42; end
    end
    c = Class.new do
      extend IncludeAny
      include_any d
      def f; super + 1; end
    end

    expect { c.new.f }.to_not raise_exception
    c.new.f.should == 43
  end

  it "should not pollute the ancestors with duplicates" do
    c = Class.new do
      extend IncludeAny
      include_any Class.new
    end

    c.ancestors.should == c.ancestors.uniq
  end
end
