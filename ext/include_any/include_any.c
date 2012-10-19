#include <ruby.h>
#include "include_any.h"

#define KLASS_OF(c) (RBASIC(c)->klass)
#define RCLASS_EXT(c) (RCLASS(c)->ptr)
#define RCLASS_SUPER(c) (RCLASS_EXT(c)->super)
#define RCLASS_IV_TBL(c) (RCLASS_EXT(c)->iv_tbl)
#define RCLASS_CONST_TBL(c) (RCLASS_EXT(c)->const_tbl)
#define RCLASS_M_TBL(c) (RCLASS(c)->m_tbl)
#define RCLASS_IV_INDEX_TBL(c) (RCLASS(c)->iv_index_tbl)

struct rb_classext_struct {
    VALUE super;
    struct st_table *iv_tbl;
    struct st_table *const_tbl;
};

static VALUE
class_alloc(VALUE flags, VALUE klass)
{
    rb_classext_t *ext = ALLOC(rb_classext_t);
    NEWOBJ(obj, struct RClass);
    OBJSETUP(obj, klass, flags);
    obj->ptr = ext;
    RCLASS_IV_TBL(obj) = 0;
    RCLASS_CONST_TBL(obj) = 0;
    RCLASS_M_TBL(obj) = 0;
    RCLASS_SUPER(obj) = 0;
    RCLASS_IV_INDEX_TBL(obj) = 0;
    return (VALUE)obj;
}

static VALUE
include_class_new(VALUE module, VALUE super)
{
    VALUE klass = class_alloc(T_ICLASS, rb_cClass);

    if (BUILTIN_TYPE(module) == T_ICLASS) {
	module = RBASIC(module)->klass;
    }
    if (!RCLASS_IV_TBL(module)) {
	RCLASS_IV_TBL(module) = st_init_numtable();
    }
    if (!RCLASS_CONST_TBL(module)) {
	RCLASS_CONST_TBL(module) = st_init_numtable();
    }
    RCLASS_IV_TBL(klass) = RCLASS_IV_TBL(module);
    RCLASS_CONST_TBL(klass) = RCLASS_CONST_TBL(module);
    RCLASS_M_TBL(klass) = RCLASS_M_TBL(module);
    RCLASS_SUPER(klass) = super;
    if (TYPE(module) == T_ICLASS) {
	RBASIC(klass)->klass = RBASIC(module)->klass;
    }
    else {
	RBASIC(klass)->klass = module;
    }
    OBJ_INFECT(klass, module);
    OBJ_INFECT(klass, super);

    return (VALUE)klass;
}

VALUE rb_include_any(VALUE klass, VALUE module)
{
    VALUE p, c;
    int changed = 0;

    rb_frozen_class_p(klass);
    if (!OBJ_UNTRUSTED(klass)) {
        rb_secure(4);
    }

    OBJ_INFECT(klass, module);
    c = klass;
    while (module) {
        int superclass_seen = 0;

        if (RCLASS_M_TBL(klass) == RCLASS_M_TBL(module))
            rb_raise(rb_eArgError, "cyclic include detected");
        /* ignore if the module included already in superclasses */
        for (p = RCLASS_SUPER(klass); p; p = RCLASS_SUPER(p)) {
            switch (BUILTIN_TYPE(p)) {
              case T_ICLASS:
                if (RCLASS_M_TBL(p) == RCLASS_M_TBL(module)) {
                    if (!superclass_seen) {
                        c = p;  /* move insertion point */
                    }
                    goto skip;
                }
                break;
              case T_CLASS:
                superclass_seen = 1;
                break;
            }
        }
        c = RCLASS_SUPER(c) = include_class_new(module, RCLASS_SUPER(c));
        if (RMODULE_M_TBL(module) && RMODULE_M_TBL(module)->num_entries)
            changed = 1;
      skip:
        module = RCLASS_SUPER(module);
    }
    if (changed) rb_clear_cache();

    return Qnil;
}

VALUE mIncludeAny;

void Init_include_any() {
  mIncludeAny = rb_define_module("IncludeAny");
  rb_define_method(mIncludeAny, "include_any", rb_include_any, 1);
}
