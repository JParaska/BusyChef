// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "UserWidgetBase.h"

#include "Blueprint/WidgetTree.h"
#include "../Characters/CharacterBase.h"

void UUserWidgetBase::ShowCharacter(ACharacterBase* Character) {
	ShownCharacter = Character;

	TArray<UWidget*> ChildWidgets;
	WidgetTree->GetAllWidgets(ChildWidgets);

	for (UWidget* Child : ChildWidgets) {
		UUserWidgetBase* ChildWidget = Cast<UUserWidgetBase>(Child);
		if (ChildWidget != nullptr) {
			ChildWidget->ShowCharacter(Character);
		}
	}
}
