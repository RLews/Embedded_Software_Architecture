


SUBDIRS = main
SUBDIRS += cJSON

.PHONY: $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	rm -f *.a $(OBJS)
	for d in $(SUBDIRS) ; do $(MAKE) -C $$d clean ; done
