LOCAL_BASE	:= Process/offset_ptr
LOCAL_MDLS	:= 
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/, $(LOCAL_MDLS))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)/*.h)
LOCAL_INCS	+= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)/*.cpp)
LOCAL_SRCS	+= $(foreach sdir, $(LOCAL_BLDS), $(wildcard $(sdir)/*.cpp))

LOCAL_OBJS	:= $(patsubst %.cpp, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.cpp, %.deps, $(LOCAL_SRCS))

SRCS		+= $(LOCAL_SRCS)
TMPS		+= $(LOCAL_OBJS)
DEPS		+= $(LOCAL_DEPS)

TARGET		:= offset_ptr
PROGRAM		:= $(addprefix $(LOCAL_BASE)/, $(TARGET))
PROGRAMS		+= $(PROGRAM)

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CXX) -MM $< > $@

$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)

$(PROGRAM): $(LOCAL_OBJS) $(OBJS) $(LIBS)
	$(CXX) $(LOCAL_OBJS) $(OBJS) $(LIBS) -o $@


