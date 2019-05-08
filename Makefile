.PHONY: clean All

All:
	@echo "----------Building project:[ documentation - Debug ]----------"
	@cd "documentation" && "$(MAKE)" -f  "documentation.mk"
clean:
	@echo "----------Cleaning project:[ documentation - Debug ]----------"
	@cd "documentation" && "$(MAKE)" -f  "documentation.mk" clean
