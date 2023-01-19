#include "AptosClient.h"
#include "PayloadBuilder.h"
#include "MathHelper.h"
#include "LibraryManager.h"

UAptosClient::UAptosClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {  }

void UAptosClient::Initialize()
{
	accountsService		= NewObject<UAccountsService>();
	blocksService		= NewObject<UBlocksService>();
	eventsService		= NewObject<UEventsService>();
	generalService		= NewObject<UGeneralService>();
	tablesService		= NewObject<UTablesService>();
	transactionsService = NewObject<UTransactionsService>();
}

FAptosAccount UAptosClient::GetAliceAccount()
{
	std::vector<uint8_t> sk
	{
		139, 232, 127, 5, 224, 205, 154, 39, 214, 116, 173, 201, 71, 84, 202, 204, 61, 237, 31, 250, 128, 105, 113, 118, 208, 237, 211, 102, 9, 223, 189, 206, 193, 197, 88, 35, 4, 67, 50, 74, 18, 149, 7, 26, 224, 242, 238, 240, 250, 171, 200, 96, 66, 64, 125, 46, 66, 88, 50, 130, 103, 53, 245, 99
	};

	FAptosAccount alice = FAptosAccount();
	alice.ExtractFromPrivateKey(sk);
	return alice;
}

FAptosAccount UAptosClient::GetBobAccount()
{
	std::vector<uint8_t> sk
	{
		108, 229, 219, 204, 239, 251, 7, 108, 251, 22, 35, 129, 121, 229, 102, 50, 185, 107, 86, 192, 194, 45, 209, 232, 72, 112, 163, 36, 39, 69, 115, 39, 138, 212, 3, 225, 51, 170, 204, 43, 249, 82, 175, 54, 9, 121, 214, 27, 32, 224, 21, 193, 194, 192, 97, 1, 147, 11, 118, 60, 16, 14, 137, 6
	};

	FAptosAccount bob = FAptosAccount();
	bob.ExtractFromPrivateKey(sk);
	return bob;
}