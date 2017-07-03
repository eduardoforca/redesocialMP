/** @file test_redesocial.cpp
 *  @brief Rotina de testes unitários da Rede Social
 *
 *  Testa as funções da biblioteca romanos.h utilizando o framework
 *  de testes Google Tests
 *  
 *	@author Eduardo Sousa (eduardoforca)
 *  @date 21 Apr 2017
 */

#include <gtest/gtest.h>
#include "redeSocial.h"
#include "grafo.h"

TEST(PessoaTest, NovaPessoaTest){
	Pessoa p = CriarPessoa("Pessoa Teste", 0);
	ASSERT_NE((Pessoa)NULL, p);
	EXPECT_EQ(strcmp(p->nome, "Pessoa Teste"), 0);
	EXPECT_EQ(p->rating_cliente, 0);
	EXPECT_EQ(p->rating_provedor, 0);
}

TEST(ProdutoTest, NovoProdutoTest){
	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	ASSERT_NE((Produto)NULL, p);
	EXPECT_EQ(strcmp(p->nome, "Carona para Samambaia"), 0);
	EXPECT_EQ(strcmp(p->descricao, "Uma carona para Q5 da Samambaia"), 0);
	EXPECT_EQ(p->tipo, SERVICO);
}

TEST(TransacaoTest, NovaTransacaoTest){
	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);

	ASSERT_EQ(t->cliente, p);
	ASSERT_EQ(t->produto, prod);
	ASSERT_EQ(t->status, PEDIDA);
	ASSERT_EQ(t->provedor, (Pessoa)NULL);
}

TEST(RedeSocialTest, NovaRedeTest){

	Rede r = CriarRede();

	ASSERT_NE((Graph) NULL, r->pessoas);
	ASSERT_EQ((List) NULL, r->transacoes);
}

TEST(RedeSocialTest, AdicionarPessoa){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);

	AdicionarPessoa(r, p);
	ASSERT_FALSE(AdicionarPessoa(r, p)) <<"Pessoa repetida foi adicionada";
}

TEST(RedeSocialTest, AdicionarProduto){
	Rede r = CriarRede();

	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarProduto(r, p);
	ASSERT_EQ(p, (Produto)r->produtos->value);
}
TEST(RedeSocialTest, AdicionarTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);

	AdicionarTransacao(r, t);
	ASSERT_EQ(t, (Transacao)r->transacoes->value);

}

TEST(RedeSocialTest, ExcluirPessoa){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);

	AdicionarPessoa(r, p);
	ASSERT_TRUE(ExcluirPessoa(r, p));
	ASSERT_FALSE(ExcluirPessoa(r, p)) <<"Reexclusao";
}

TEST(RedeSocialTest, ExcluirProduto){
	Rede r = CriarRede();

	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarProduto(r, p);
	ASSERT_TRUE(ExcluirProduto(r, p));
	ASSERT_FALSE(ExcluirProduto(r, p)) <<"Reexclusao";
}
TEST(RedeSocialTest, ExcluirTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);

	AdicionarTransacao(r, t);
	ASSERT_TRUE(ExcluirTransacao(r, t));
	ASSERT_FALSE(ExcluirTransacao(r, t));
}
TEST(RedeSocialTest, DeletaRede){
	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarPessoa(r, p);
	AdicionarProduto(r, prod);
	AdicionarTransacao(r, t);

	ASSERT_TRUE(DeletaRede(r));
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}