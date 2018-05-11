LOCAL_BASE	:= Process/Reciever
LOCAL_MDLS	:= 
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/,$(LOCAL_MDLS))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)/*.h)
LOCAL_INCS	+= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

CHILD_SRCS	:= $(wildcard $(LOCAL_BASE)/*.cpp)
CHILD_SRCS	+= $(foreach sdir,$(LOCAL_BLDS),$(wildcard $(sdir)/*.cpp))

CHILD_OBJS	:= $(patsubst %.cpp, %.o,$(CHILD_SRCS))
LOCAL_DEPS	:= $(patsubst %.cpp, %.deps,$(CHILD_SRCS))

#SRCS		+= $(CHILD_SRCS)
TMPS		+= $(CHILD_OBJS)
DEPS		+= $(LOCAL_DEPS)

TARGET		:= Reciever
CHILD		:= $(addprefix $(LOCAL_BASE)/,$(TARGET))
PROGRAMS	+= $(CHILD)

$(LOCAL_DEPS): $(CHILD_SRCS) $(LOCAL_INCS)
	@$(CXX) -MM $< > $@

$(CHILD_OBJS): $(CHILD_SRCS) $(LOCAL_DEPS)

$(CHILD): $(CHILD_OBJS) $(OBJS) $(LIBS)
	$(CXX) $(CHILD_OBJS) $(OBJS) $(LIBS) -o $@


