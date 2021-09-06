


SUBDIRS = main
SUBDIRS += cJSON
SUBDIRS += easylogger easylogger/inc easylogger/port easylogger/src easylogger/plugins easylogger/plugins/file
SUBDIRS += Debug_Cmd

.PHONY: $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	rm -f *.a $(OBJS)
	for d in $(SUBDIRS) ; do $(MAKE) -C $$d clean ; done
