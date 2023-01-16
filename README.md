# Aptos SDK

Demonstrates the integration of Aptos Blockchain in Unreal Engine in accordance with the [Aptos Official Blochain API](https://fullnode.devnet.aptoslabs.com/v1/spec#/). The current project is only for Windows platform.

## What's New

This project shows the following transactions using Aptos Blockchain.

How to transfer coin(s) from one account to another account?

How to get coin balance for an account?

How to create a collection?

How to create a token in a collection?

How to offer a token to another account?

How to claim a token which was offered?

How to cancel an offered token?

Before proceeding with anything else lets understand how transactions are submitted to the Aptos Blockchain.

Names such as 'Alice' or 'Bob' used in this documentation are used for demonstration purposes.

## SUBMIT A TRANSACTION
These are the steps to submit a transaction in Aptos.

1. To create a raw transaction we create an [Encode Submission Request](https://fullnode.devnet.aptoslabs.com/v1/spec#/schemas/EncodeSubmissionRequest) using GetEncodeSubmissionRequest function having the following variables:

- sender
- sequence_number
- max_gas_amount
- gas_unit_price
- expiration_timestamp_secs
- payload -> { type, function, type_arguments, arguments }
- secondary_signers

2. Call [Encode Submission](https://fullnode.devnet.aptoslabs.com/v1/spec#/operations/encode_submission) with the above request as a body to get a BCS (Binary Canonical Serialization) message.
3. Sign the BCS message using SignMessage function to get a signature.
4. Create a transaction signature by calling GetTransactionSignature.
5. Create a submit transaction request by calling GetSubmitTransactionRequest.
6. Call SubmitTransaction with the submit transaction request created to get the tranaction hash.

All the steps above and below are performed in the AptosClient.cpp ("UnrealAptosSDK\Plugins\AptosSDK\Source\AptosSDK\Private") folder which are called from Unreal's Widget_Menu Blueprint.

The method to get the reference to AptosClient.cpp is shown in Blueprint below:

<img width="610" alt="0" src="https://user-images.githubusercontent.com/99165088/204406621-1ca54004-cc83-4036-b052-6ffe875a6d9f.png">


## TRANSFERRING COIN
Transfers the specified amount of coins from one account to another account.

To transfer coin(s) from an account to another account we need to provide the sender account, receiver account and the amount of coin to be transfered.

<img width="473" alt="TransferCoin" src="https://user-images.githubusercontent.com/99165088/211152026-523afb30-6056-4cfc-8f50-9d7c998d94bc.png">

## GET COIN BALANCE
Gets the coin balance for the specified account.

To get the coin balance of an account we need to provide the account.

<img width="485" alt="GetCoinBalance" src="https://user-images.githubusercontent.com/99165088/211152063-b506b6a0-4d48-4350-bb19-e6a64889d2ca.png">


## CREATING COLLECTION
Create a new collection for the specified account.

To create a new collection we need to provide a collection name, collection description, uri, a max amount that the collection can hold which is shown in the blueprint below.

<img width="1067" alt="CreateCollection" src="https://user-images.githubusercontent.com/99165088/211152144-2c03d86b-1443-4deb-94b7-bc9165ff0623.png">


## CREATING TOKEN
Creates a new token in the specified collection.

To create a new token within the collection we need to provide the collection name, token name, token description, token supply, token uri, max supply (The maximum number of tokens that can be minted from this token) which is shown in the blueprint below.

<img width="1066" alt="CreateToken" src="https://user-images.githubusercontent.com/99165088/211152158-f5da9a53-f085-4c66-8232-5c4c31baafa4.png">


## OFFERING A TOKEN
Transfer a specified amount of tokens from account to receiver.

To transfer token from one account to another we need to provide the receiver address, creator address, collection name, token name, amount of tokens to be transfered which is shown in the blueprint below.

<img width="1065" alt="OfferToken" src="https://user-images.githubusercontent.com/99165088/211152166-d3fc4d83-ead2-4eb8-8a09-b75ddf5c6b33.png">


## CLAIMING A TOKEN
Claim token on specified account.

To claim token on a specified account we need to provide the sender address, creator address, collection name, and token name which is shown in the blueprint below.

<img width="1065" alt="ClaimToken" src="https://user-images.githubusercontent.com/99165088/211152179-ae8c38ca-253d-4de9-8fd2-324a4e6d8c8b.png">


## CANCELING AN OFFERED TOKEN
Cancels a pending token that was offered to a another account to claim.

To cancel a pending offered token we need to provide the receiver account, creator account, collection name and the token name.

<img width="1064" alt="CancelTokenOffered" src="https://user-images.githubusercontent.com/99165088/211152192-73bd5ca5-74fb-48d0-a94c-060a903e6e83.png">

Please feel free to to use the SDK and update us on things that come to your attention.
Thanks!
