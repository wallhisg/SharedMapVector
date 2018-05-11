LOCAL_BASE	:= Process/Sender
LOCAL_MDLS	:=
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/,$(LOCAL_MDLS))

LOCAL_INCS	:= $(wildcard $(LOCAL_BASE)/*.h)
LOCAL_INCS	+= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

PARENT_SRCS	:= $(wildcard $(LOCAL_BASE)/*.cpp)
PARENT_SRCS	+= $(foreach sdir, $(LOCAL_BLDS),$(wildcard $(sdir)/*.cpp))

PARENT_OBJS	:= $(patsubst %.cpp,%.o,$(PARENT_SRCS))
LOCAL_DEPS	:= $(patsubst %.cpp,%.deps,$(PARENT_SRCS))

#SRCS		+= $(PARENT_SRCS)
TMPS		+= $(PARENT_OBJS)
DEPS		+= $(LOCAL_DEPS)

TARGET		:= Sender
PARENT		:= $(addprefix $(LOCAL_BASE)/,$(TARGET))
PROGRAMS	+= $(PARENT)

$(LOCAL_DEPS): $(PARENT_SRCS) $(LOCAL_INCS)
	@$(CXX) -MM $< > $@

$(PARENT_OBJS): $(PARENT_SRCS) $(LOCAL_DEPS)

$(PARENT): $(PARENT_OBJS) $(OBJS) $(LIBS)
	$(CXX) $(PARENT_OBJS) $(OBJS) $(LIBS) -o $@


