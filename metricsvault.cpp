/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/eosio.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/print.hpp>
#include <string>

using eosio::indexed_by;
using eosio::const_mem_fun;
using std::string;

struct hi {
    account_name account;
};

class addressbook : public eosio::contract {
   public:
      explicit addressbook(action_name self)
              : contract(self) {
      }

      //@abi action
      void registerbio(const account_name account, const std::vector<uint64_t>& vault ) {

          // if not authorized then this action is aborted and transaction is rolled back
          // any modifications by other actions are undone
          require_auth(account); // make sure authorized by account

          // address_index is typedef of our multi_index over table address
          // address table is auto "created" if needed
          address_index addresses(_self, _self); // code, scope

          // verify the record does not already exist
          // multi_index find on primary index which in our case is account
          auto itr = addresses.find(account);
          eosio_assert(itr == addresses.end(), "Address for account already exists");

          // add to table, first argument is account to bill for storage
          // each entry will be billed to the associated account
          // we could have instead chosen to bill _self for all the storage
		 // in which case the contract is responsible for the RAM
          addresses.emplace(account /*payer*/, [&](auto& address) {
              address.accountname = account;
              address.vault = vault;
          });
          eosio::print(account,vault[0]);


      }

      //@abi action
      void update(const account_name account, const std::vector<uint64_t>& vault ) {

          require_auth(account); // make sure authorized by account

          address_index addresses(_self, _self); // code, scope

          // verify that the record already exist
          auto itr = addresses.find(account);
          eosio_assert(itr != addresses.end(), "Address for account not found");

          addresses.modify( itr, account /*payer*/, [&]( auto& address ) {
              address.accountname = account;
              address.vault = vault;
          });

      }

      //@abi action
      void remove(const account_name account) {
          require_auth(account); // make sure authorized by account

          address_index addresses(_self, _self); // code, scope

          // verify already exist
          auto itr = addresses.find(account);
          eosio_assert(itr != addresses.end(), "Address for account not found");

          addresses.erase( itr );
      }


    //@abi action
    void authorizebio(const account_name account, const std::vector<uint64_t>& vault ) {
        require_auth(account); // make sure authorized by account

        address_index addresses(_self, _self); // code, scope

        // verify that the record already exist
        auto itr = addresses.find(account);
        eosio_assert(itr != addresses.end(), "Address for account not found");
    }

   private:

      //@abi table metrict i64
      struct address {
          uint64_t accountname;
          std::vector<uint64_t> vault;

          uint64_t primary_key() const { return accountname; }
      };

      typedef eosio::multi_index< N(metrict), address> address_index;

};

EOSIO_ABI( addressbook, (registerbio)(update)(remove)(authorizebio) )