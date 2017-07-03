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
	Pessoa p = CriarPessoa("Pessoa Teste");
	ASSERT_NE((Pessoa)NULL, p);
	EXPECT_EQ(strcmp(p->nome, "Pessoa Teste"), 0);
	EXPECT_EQ(p->rating_cliente, 0);
	EXPECT_EQ(p->rating_provedor, 0);
}

TEST(ProdutoTest, NovoProdutoTest){
	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO);
	ASSERT_NE((Produto)NULL, p);
	EXPECT_EQ(strcmp(p->nome, "Carona para Samambaia"), 0);
	EXPECT_EQ(strcmp(p->descricao, "Uma carona para Q5 da Samambaia"), 0);
	EXPECT_EQ(p->tipo, SERVICO);
}

TEST(TransacaoTest, NovaTransacaoTest){
	Pessoa p = CriarPessoa("Pessoa");
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO);
	Transacao t = CriarTransacao(p, prod);

	ASSERT_EQ(t->provedor, p);
	ASSERT_EQ(t->produto, prod);
	ASSERT_EQ(t->status, PEDIDA);
	ASSERT_EQ(t->cliente, (Pessoa)NULL);
}

TEST(RedeSocialTest, NovaRedeTest){

	Rede r = CriarRede();

	ASSERT_NE((Graph) NULL, r->pessoas);
	ASSERT_EQ((List) NULL, r->transacoes);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}