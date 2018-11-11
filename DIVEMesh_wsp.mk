.PHONY: clean All

All:
	@echo "----------Building project:[ DIVEMesh - Release ]----------"
	@$(MAKE) -f  "DIVEMesh.mk"
clean:
	@echo "----------Cleaning project:[ DIVEMesh - Release ]----------"
	@$(MAKE) -f  "DIVEMesh.mk" clean
