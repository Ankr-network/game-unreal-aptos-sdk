# Aptos SDK

This project demonstrates the integration of Aptos Blockchain in Unreal Engine in accordance with the [Aptos Official Blochain API](https://fullnode.devnet.aptoslabs.com/v1/spec#/operations/get_transactions). The current project is only tested on Windows platform as the development is in its initial stage.

This project shows how to transfer coin(s) from one person to another using Aptos API. 
These are the steps that are taken to make the transaction.
All the functions described in the steps are inside AptosClient.cpp inside the "UnrealAptosSDK\Plugins\AptosSDK\Source\AptosSDK\Private" folder which are called from Blueprint.

The method to get the reference to AptosClient.cpp is shown in Blueprint below:

<img width="610" alt="0" src="https://user-images.githubusercontent.com/99165088/204406621-1ca54004-cc83-4036-b052-6ffe875a6d9f.png">

Lets start the steps to make a coin transfer using Aptos.

## Steps

1. Create an encode submission request to prepare a raw transaction to be sent to Aptos for serialization.
2. Call EncodeSubmission function with the request created to get a BCS (Binary Canonical Serialization) data.
3. Sign and create a transaction signature Scheme by calling GetTransactionSignature containing the BCS data to sign.
4. Create a submit transaction request by calling GetSubmitTransactionRequest.
5. Call SubmitTransaction with the request created to get the tranaction hash.

## Step 1

### GetEncodeSubmissionRequest
Call GetEncodeSubmissionRequest function to create a raw transaction request to be sent to Aptos for serialization.

Whats happening in this function is to create a raw transaction that contains information as a payload for a function to be executed in an Aptos Module (Contract). For details on what is a module in Aptos kindly refer to this [link](https://aptos.dev/).

<img width="526" alt="1" src="https://user-images.githubusercontent.com/99165088/204404698-2744c79b-de1c-4eda-9a2f-8adb9b6470ac.png">


## Step 2

### EncodeSubmission
Call EncodeSubmission function with the encode submission request created to obtain a BCS serialized data.

Whats happening in this function is to send the raw transaction request to Aptos to serialize the data for us, as BCS serialization plugin is available only for Rust, Python and Typescript at the moment so Aptos provides one for us, see [here](https://fullnode.devnet.aptoslabs.com/v1/spec#/operations/encode_submission).

<img width="769" alt="2" src="https://user-images.githubusercontent.com/99165088/204404841-c64c946d-d000-4619-8735-65e133c132a1.png">

## Step 3

### GetTransactionSignature
Call GetTransactionSignature function to sign the BCS data and to create a transaction signature scheme.

Whats happening in this function is to sign the BCS data obtained from Aptos using the sender's account.

<img width="769" alt="3" src="https://user-images.githubusercontent.com/99165088/204405080-0dc72e62-79e6-4a3a-8b38-b2bcd82f7b9f.png">

## Step 4

### GetTransactionSubmitRequest
Call GetTransactionSubmitRequest function to create a transaction request ready to submit to Aptos.

Whats happening here is to just prepare a transaction request ready to be submitted with all the essential information obtained.

<img width="710" alt="4" src="https://user-images.githubusercontent.com/99165088/204405117-a9d7e147-99ac-4616-a191-c7824624f6ea.png">


## Step 5

### Submit Transaction
Call SubmitTransaction function with the request created to obtain the hash the transaction.
<img width="697" alt="5" src="https://user-images.githubusercontent.com/99165088/204405407-b64eba4c-460e-4022-bae7-e8e9aa296327.png">

Please feel free to to use the SDK and update us on things that come to your attention.
Thanks!
