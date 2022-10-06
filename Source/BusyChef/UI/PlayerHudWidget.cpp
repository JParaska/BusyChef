// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "PlayerHudWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"

#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UPlayerHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetOwningPlayer() != nullptr && ReticleImage != nullptr) {
		TObjectPtr<UCanvasPanelSlot> PanelSlot = Cast<UCanvasPanelSlot>(ReticleImage->Slot);
		if (PanelSlot != nullptr) {
			FVector2D Position;
			UWidgetLayoutLibrary::GetMousePositionScaledByDPI(GetOwningPlayer(), Position.X, Position.Y);
			PanelSlot->SetPosition(Position);
		}
	}
}
